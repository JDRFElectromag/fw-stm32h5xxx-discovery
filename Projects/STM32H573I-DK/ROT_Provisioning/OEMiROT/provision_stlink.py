"""
This script is similar to provision_jlink.py, but uses STLINK so the MCU can remain in OPEN state.
This behavior appears to be undocumented.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path
from intelhex import IntelHex

SCRIPT_DIR = Path(__file__).resolve().parent
OEMIROT_DIR = SCRIPT_DIR

CLI = "STM32_Programmer_CLI"
TPC_CLI = "STM32TrustedPackageCreator_CLI"

DA_OBKEY = (OEMIROT_DIR / "../DA/Binary/DA_Config.obk").resolve()
OEMIROT_CONFIG_OBKEY = (OEMIROT_DIR / "Binary/OEMiRoT_Config.obk").resolve()
OEMIROT_DATA_OBKEY = (OEMIROT_DIR / "Binary/OEMiRoT_Data.obk").resolve()

FWTHOR_BOOT_HEX_REL = Path(
    "appProcessor/bootloader/mcuboot/build/debug/stm32h573i-dk/"
    "autonomySensor_mcuboot_sec_stm32h573i-dk.hex"
)
FWTHOR_APP_HEX_REL = Path(
    "appProcessor/applications/blinky/build/debug/stm32h573i-dk/with_mcuboot/"
    "autonomySensor_blinky_with_mcuboot_sec_signed_stm32h573i-dk.hex"
)
FWTHOR_APP_INPUT_HEX_REL = Path(
    "appProcessor/applications/blinky/build/debug/stm32h573i-dk/with_mcuboot/"
    "autonomySensor_blinky_with_mcuboot_sec_stm32h573i-dk.hex"
)

OPEN_STATE_HEX = "0XED"


def run_cli(args: list[str], *, check: bool = True) -> subprocess.CompletedProcess[str]:
    cmd = [CLI] + args
    print("+", " ".join(cmd))
    proc = subprocess.run(cmd, text=True, capture_output=True)
    if proc.stdout:
        print(proc.stdout, end="")
    if proc.stderr:
        print(proc.stderr, end="", file=sys.stderr)

    if check and proc.returncode != 0:
        raise RuntimeError(f"Command failed with exit code {proc.returncode}")
    return proc


def run_tpc(args: list[str], *, check: bool = True) -> subprocess.CompletedProcess[str]:
    cmd = [TPC_CLI] + args
    print("+", " ".join(cmd))
    proc = subprocess.run(cmd, text=True, capture_output=True)
    if proc.stdout:
        print(proc.stdout, end="")
    if proc.stderr:
        print(proc.stderr, end="", file=sys.stderr)

    if check and proc.returncode != 0:
        raise RuntimeError(f"Command failed with exit code {proc.returncode}")
    return proc


def build_connection(speed: str, ap: str, mode: str, reset: str | None = None) -> str:
    parts = ["port=SWD", f"speed={speed}", f"ap={ap}", f"mode={mode}"]
    if reset:
        parts.append(f"reset={reset}")
    return " ".join(parts)


def list_probes() -> None:
    # Useful for diagnostics when users hit "No debug probe detected".
    run_cli(["-l"], check=False)


def connect(connection: str) -> None:
    run_cli(["-c", connection])


def halt_core(connection: str) -> None:
    """Halt the core. Use UR mode connection to prevent unhalt on disconnect."""
    run_cli(["-c", connection, "-halt"])


def hard_reset(connection: str) -> None:
    """Hardware reset. With UR mode, core stays under reset even on disconnect."""
    run_cli(["-c", connection, "-hardRst"])


def mass_erase(connection: str) -> None:
    """Erase all flash. Core must be halted before and after to prevent execution."""
    run_cli(["-c", connection, "-e", "all"])


def program_hex(connection: str, image: Path) -> None:
    """
    Program HEX file. With UR mode connection, target stays under reset.
    Caller must halt before and after to ensure core doesn't run on reconnect.
    """
    run_cli(["-c", connection, "-d", str(image), "-v"])


def read_ob_display(connection: str) -> str:
    proc = run_cli(["-c", connection, "-ob", "displ"], check=False)
    return ((proc.stdout or "") + "\n" + (proc.stderr or "")).upper()


def is_open_state(ob_text: str) -> bool:
    # Accept both named and hex representations across CubeProg versions.
    if re.search(r"PRODUCT_STATE[^\n]*OPEN", ob_text):
        return True
    if re.search(r"PRODUCT_STATE[^\n]*0XED", ob_text):
        return True
    return False


def assert_open_state(connection: str, where: str) -> None:
    ob_text = read_ob_display(connection)
    if not is_open_state(ob_text):
        raise RuntimeError(
            "Product state is not OPEN at "
            f"{where}. Aborting to avoid changing lifecycle unexpectedly."
        )


def write_ob(connection: str, register_name: str, value: int) -> None:
    """Write option byte register."""
    value_hex = f"0x{value:08X}"
    print(f"Writing OB: {register_name} = {value_hex}")
    run_cli(["-c", connection, "-ob", f"{register_name}={value_hex}"])


def read_ob(connection: str, register_name: str) -> str:
    """Read option byte register."""
    print(f"Reading OB: {register_name}")
    proc = run_cli(["-c", connection, "-ob", register_name, "displ"], check=False)
    return ((proc.stdout or "") + "\n" + (proc.stderr or ""))


def pack_start_end(start: int, end: int) -> int:
    """Pack watermark start/end into register value."""
    return ((end & 0xFF) << 16) | (start & 0xFF)


def pack_secboot(lock: int, secbootadd: int) -> int:
    """Pack SECBOOT_LOCK and secure boot address into register value."""
    return ((secbootadd & 0x00FFFFFF) << 8) | (lock & 0xFF)


def program_option_bytes_step1(connection: str) -> None:
    """
    Program critical option bytes that affect memory mapping.
    Must be done before firmware programming.
    - FLASH_OPTSR2: Enable TrustZone (TZEN=0xB4)
    - FLASH_SECBOOTR: Secure boot address (0xC0000) + unlocked (0xC3)
    - FLASH_SECWM1R/2R: Secure watermarks disabled
    """
    print("Programming option bytes step 1 (TrustZone + secure boot config)...")

    # TZEN=0xB4 enables TrustZone
    # SRAM1_3_RST=1, SRAM3_ECC=1, SRAM2_ECC=0, BKPRAM_ECC=1
    write_ob(connection, "FLASH_OPTSR2", 0xB4000034)

    # Secure boot at 0xC0000, unlocked (0xC3) to allow programming
    write_ob(connection, "FLASH_SECBOOTR", pack_secboot(0xC3, 0xC0000))

    # Disable secure watermarks (start=0x7F > end=0x00 means disabled)
    write_ob(connection, "FLASH_SECWM1R", pack_start_end(0x7F, 0x00))
    write_ob(connection, "FLASH_SECWM2R", pack_start_end(0x7F, 0x00))


def program_option_bytes_step2(connection: str) -> None:
    """
    Program additional option bytes after firmware is flashed.
    - FLASH_WRP1R/2R: Write protection disabled
    - FLASH_HDP1R/2R: Hide protection disabled
    """
    print("Programming option bytes step 2 (write/hide protection)...")

    # Disable write protection
    write_ob(connection, "FLASH_WRP1R", 0xFFFFFFFF)
    write_ob(connection, "FLASH_WRP2R", 0xFFFFFFFF)

    # Disable hide protection (start=0x7F > end=0x00 means disabled)
    write_ob(connection, "FLASH_HDP1R", pack_start_end(0x7F, 0x00))
    write_ob(connection, "FLASH_HDP2R", pack_start_end(0x7F, 0x00))


def program_option_bytes_secure_boot_lock(connection: str) -> None:
    """
    Lock the secure boot register after firmware is programmed.
    Changes SECBOOT_LOCK from 0xC3 (unlocked) to 0xB4 (locked).
    """
    print("Locking secure boot option byte...")
    # write_ob(connection, "FLASH_SECBOOTR", pack_secboot(0xB4, 0xC0000))

def program_obk(connection: str, obk: Path) -> None:
    run_cli(["-c", connection, "-sdp", str(obk)])

def prompt_boot0_position(position: int) -> None:
    if position not in (0, 1):
        raise ValueError("BOOT0 position must be 0 or 1")

    vdd_text = "disconnected from VDD" if position == 0 else "connected to VDD"
    print("=====")
    print(f"Set BOOT0 pin {vdd_text}")
    print(f"STM32H573I-DK: set SW1 to position {position}")
    input("Press Enter to continue...")


def require_obk_files(obk_files: list[Path]) -> None:
    missing = [p for p in obk_files if not p.exists()]
    if missing:
        missing_str = "\n".join(f"- {p}" for p in missing)
        raise FileNotFoundError(f"Missing OBK file(s):\n{missing_str}")


def require_files(label: str, files: list[Path]) -> None:
    missing = [p for p in files if not p.exists()]
    if missing:
        missing_str = "\n".join(f"- {p}" for p in missing)
        raise FileNotFoundError(f"Missing {label} file(s):\n{missing_str}")


def merge_hex_files(boot_hex: Path, app_hex: Path, output_hex: Path) -> None:
    print(f"+ Merging {boot_hex.name} and {app_hex.name}")

    boot = IntelHex(str(boot_hex))
    app = IntelHex(str(app_hex))

    boot.merge(app, overlap='error')

    boot.write_hex_file(str(output_hex))
    print(f"  -> {output_hex.name}")


def read_min_address_from_intel_hex(hex_file: Path) -> int:
    ih = IntelHex(str(hex_file))
    return ih.minaddr()

def _set_xml_param_value(root: ET.Element, param_name: str, value: str) -> None:
    for param in root.findall(".//Param"):
        name_node = param.find("Name")
        if name_node is not None and (name_node.text or "").strip() == param_name:
            value_node = param.find("Value")
            if value_node is None:
                value_node = ET.SubElement(param, "Value")
            value_node.text = value
            return
    raise RuntimeError(f"Param '{param_name}' not found in XML template")


def _set_xml_output_value(root: ET.Element, output_name: str, value: str) -> None:
    for output in root.findall(".//Output"):
        name_node = output.find("Name")
        if name_node is not None and (name_node.text or "").strip() == output_name:
            value_node = output.find("Value")
            if value_node is None:
                value_node = ET.SubElement(output, "Value")
            value_node.text = value
            return
    raise RuntimeError(f"Output '{output_name}' not found in XML template")

def create_temp_signed_image_xml(
    base_xml: Path,
    firmware_input_hex: Path,
    image_output_hex: Path,
    output_xml: Path,
    header_size: int = 0x400,
) -> Path:
    """Create a temporary XML with updated input/output/offset for TPC signing."""
    app_start_address = read_min_address_from_intel_hex(firmware_input_hex)
    exec_offset = app_start_address - header_size
    if exec_offset < 0:
        raise RuntimeError(
            f"Computed execution offset is negative: start=0x{app_start_address:X}, "
            f"header=0x{header_size:X}"
        )

    # Read the base XML and perform string replacements
    # This preserves the exact XML format TPC expects
    xml_content = base_xml.read_text(encoding="utf-8")

    # Ensure we have absolute paths for TPC
    firmware_input_abs = firmware_input_hex.resolve()
    image_output_abs = image_output_hex.resolve()

    # Resolve LinkedXML path (../Config/OEMiRoT_Config.xml) to absolute
    linked_xml_abs = (base_xml.parent / "../Config/OEMiRoT_Config.xml").resolve()

    # Find and replace the three values we need to update
    import re

    # Replace firmware input file path
    xml_content = re.sub(
        r'(<Name>Firmware binary input file</Name>\s*<Value>)[^<]*(</Value>)',
        rf'\g<1>{str(firmware_input_abs)}\g<2>',
        xml_content,
        flags=re.DOTALL
    )

    # Replace execution offset
    xml_content = re.sub(
        r'(<Name>Firmware execution area offset</Name>\s*<Value>)[^<]*(</Value>)',
        rf'\g<1>0x{exec_offset:X}\g<2>',
        xml_content,
        flags=re.DOTALL
    )

    # Replace LinkedXML path with absolute path
    xml_content = re.sub(
        r'(<LinkedXML>)[^<]*(</LinkedXML>)',
        rf'\g<1>{str(linked_xml_abs)}\g<2>',
        xml_content,
        flags=re.DOTALL
    )

    # Replace output file path
    xml_content = re.sub(
        r'(<Name>Image output file</Name>\s*<Value>)[^<]*(</Value>)',
        rf'\g<1>{str(image_output_abs)}\g<2>',
        xml_content,
        flags=re.DOTALL
    )

    output_xml.write_text(xml_content, encoding="utf-8")

    # TEMPORARY: Save a copy to Downloads for inspection
    # import shutil
    # debug_xml = Path.home() / "Downloads" / "OEMiROT_S_Code_Init_Image_DEBUG.xml"
    # shutil.copy2(output_xml, debug_xml)
    # print(f"DEBUG: XML saved to {debug_xml}")

    return output_xml


def parse_cli_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "ST-LINK provisioning helper for OEMiROT OBKs. "
            "This script never writes PRODUCT_STATE and enforces OPEN state."
        )
    )

    # Keep high-level action flags similar to provision_jlink.py.
    parser.add_argument(
        "--debug-access",
        action="store_true",
        help="Probe/connect diagnostics and product state display only.",
    )
    parser.add_argument(
        "--factory-reset",
        action="store_true",
        help="Mass erase user flash only (no product-state change).",
    )
    parser.add_argument(
        "--provision",
        action="store_true",
        help="Provision DA/OEMiROT OBKs while preserving OPEN state.",
    )

    # ST-LINK connection arguments.
    parser.add_argument("--speed", default="reliable", help="SWD speed value for STM32_Programmer_CLI")
    parser.add_argument("--ap", default="0", help="SWD AP index")
    parser.add_argument("--mode", default="Hotplug", help="Connection mode")

    parser.add_argument(
        "--fwthor",
        type=Path,
        required=False,
        help=(
            "Path to fw-thor root. App/boot HEX paths are derived from this root "
            "using the existing layout from provision_jlink.py."
        ),
    )

    return parser.parse_args()


def main() -> int:
    args = parse_cli_args()
    connection = build_connection(args.speed, args.ap, args.mode)
    # During provisioning, use Under Reset (UR) mode with HWrst to ensure the core
    # cannot run even during ST-LINK disconnect/reconnect cycles between operations.
    # UR mode keeps the target under hardware reset, preventing code execution.
    provision_connection = build_connection(args.speed, args.ap, "UR", "HWrst")

    # If no action was selected, behave like a minimal health check.
    if not (args.debug_access or args.factory_reset or args.provision):
        print("No action selected. Running connectivity + OPEN-state check.")
        list_probes()
        connect(connection)
        assert_open_state(connection, "startup")
        print("Probe detected and OPEN state confirmed.")
        return 0

    if args.debug_access:
        list_probes()
        connect(connection)
        assert_open_state(connection, "debug-access")
        print("Debug-access checks completed.")

    if args.factory_reset:
        connect(connection)
        assert_open_state(connection, "factory-reset precondition")
        mass_erase(connection)
        hard_reset(connection)
        assert_open_state(connection, "factory-reset postcondition")
        print("Factory-reset flow completed (mass erase only).")

    if args.provision:
        if args.fwthor is None:
            raise RuntimeError("--provision requires --fwthor")

        app_init_xml_base = (OEMIROT_DIR / "Images/OEMiROT_S_Code_Init_Image.xml").resolve()

        fwthor_root = args.fwthor.resolve()
        app_input_hex = (fwthor_root / FWTHOR_APP_INPUT_HEX_REL).resolve()
        app_signed_hex = (fwthor_root / FWTHOR_APP_HEX_REL).resolve()

        boot_hex = (fwthor_root / FWTHOR_BOOT_HEX_REL).resolve()

        require_files("image", [app_init_xml_base, app_input_hex, boot_hex])
        obk_files = [DA_OBKEY, OEMIROT_CONFIG_OBKEY, OEMIROT_DATA_OBKEY]
        require_obk_files(obk_files)

        # BOOT0 low during flash/programming stage.
        prompt_boot0_position(0)

        with tempfile.TemporaryDirectory(prefix="oemirot_tpc_") as tmp_dir:

            # Update the xml file automatically
            app_init_xml_tmp = Path(tmp_dir) / "OEMiROT_S_Code_Init_Image.tmp.xml"
            merged_hex = Path(tmp_dir) / "merged_signed_app_boot.hex"
            create_temp_signed_image_xml(
                base_xml=app_init_xml_base,
                firmware_input_hex=app_input_hex,
                image_output_hex=app_signed_hex,
                output_xml=app_init_xml_tmp,
                header_size=0x400,
            )

            # Sign the apphex using the generated hex file
            run_tpc(["-pb", str(app_init_xml_tmp)])

            # Merge the hex file
            require_files("signed image", [app_signed_hex])
            merge_hex_files(boot_hex, app_signed_hex, merged_hex)
            require_files("merged image", [merged_hex])

            print("\n=== Step 1: Programming critical option bytes ===")
            assert_open_state(connection, "before OB step 1")
            hard_reset(provision_connection)
            halt_core(provision_connection)
            mass_erase(provision_connection)
            program_option_bytes_step1(provision_connection)
            halt_core(provision_connection) # Just for sanity core shouldn't be running

            # Program firmware with core kept halted
            print(f"\n=== Step 2: Programming firmware ===")
            print(f"Programming merged HEX: {merged_hex}")
            program_hex(provision_connection, merged_hex)

        # BOOT0 high for OBK provisioning stage.
        prompt_boot0_position(1)

        # Program option bytes step 2: write/hide protection
        # Done after firmware with BOOT0=1 to prevent bootloader from running
        print("\n=== Step 3: Programming additional option bytes ===")
        program_option_bytes_step2(provision_connection)

        # Lock the secure boot register so MCU will boot properly
        print("\n=== Step 4: Locking secure boot register ===")
        program_option_bytes_secure_boot_lock(provision_connection)

        # Program OBKs using system bootloader (BOOT0=1)
        print("\n=== Step 5: Programming OBK files ===")
        for obk in obk_files:
            print(f"Provisioning OBK via SDP: {obk}")
            program_obk(connection, obk)

        # Return BOOT0 to normal boot position.
        prompt_boot0_position(0)

        # Verify one last time that we're still in OPEN state and halted.
        assert_open_state(connection, "final verification")
        print("Provisioning completed with product state kept OPEN.")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
