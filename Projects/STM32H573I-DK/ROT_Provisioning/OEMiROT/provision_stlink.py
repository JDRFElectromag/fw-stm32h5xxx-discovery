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


def program_obk(connection: str, obk: Path) -> None:
    """
    Program OBK via SDP (Secure Data Programming).
    Multiple halt guards ensure core stays halted across reset and SDP operations.
    UR mode connection prevents core from running during ST-LINK reconnects.
    """
    halt_core(connection)
    halt_core(connection)
    run_cli(["-c", connection, "-sdp", str(obk)])
    halt_core(connection)


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
    """Merge bootloader and application HEX files using srec_cat."""
    cmd = [
        "srec_cat",
        str(boot_hex), "-Intel",
        str(app_hex), "-Intel",
        "-o", str(output_hex), "-Intel",
    ]
    print("+", " ".join(cmd))
    proc = subprocess.run(cmd, text=True, capture_output=True)
    if proc.stdout:
        print(proc.stdout, end="")
    if proc.stderr:
        print(proc.stderr, end="", file=sys.stderr)
    if proc.returncode != 0:
        raise RuntimeError(
            f"HEX merge failed with exit code {proc.returncode}. "
            "Ensure srec_cat (SRecord) is installed."
        )


def read_min_address_from_intel_hex(hex_file: Path) -> int:
    """Return the minimum absolute data address in an Intel HEX file."""
    min_addr: int | None = None
    linear_base = 0
    segment_base = 0

    with hex_file.open("r", encoding="utf-8") as f:
        for raw_line in f:
            line = raw_line.strip()
            if not line:
                continue
            if not line.startswith(":") or len(line) < 11:
                raise RuntimeError(f"Invalid Intel HEX line in {hex_file}: {line}")

            byte_count = int(line[1:3], 16)
            address = int(line[3:7], 16)
            record_type = int(line[7:9], 16)
            data = line[9:9 + (byte_count * 2)]

            if record_type == 0x00:
                base = linear_base if linear_base != 0 else segment_base
                abs_addr = base + address
                if min_addr is None or abs_addr < min_addr:
                    min_addr = abs_addr
            elif record_type == 0x04:
                # Extended linear address record: upper 16 bits.
                linear_base = int(data, 16) << 16
                segment_base = 0
            elif record_type == 0x02:
                # Extended segment address record: bits 4..19.
                segment_base = int(data, 16) << 4
                linear_base = 0
            elif record_type == 0x01:
                break

    if min_addr is None:
        raise RuntimeError(f"No data records found in HEX file: {hex_file}")
    return min_addr


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
    # Register XML namespaces to preserve them when writing
    ET.register_namespace('xsi', 'http://www.w3.org/2001/XMLSchema-instance')

    tree = ET.parse(base_xml)
    root = tree.getroot()

    app_start_address = read_min_address_from_intel_hex(firmware_input_hex)
    exec_offset = app_start_address - header_size
    if exec_offset < 0:
        raise RuntimeError(
            f"Computed execution offset is negative: start=0x{app_start_address:X}, "
            f"header=0x{header_size:X}"
        )

    _set_xml_param_value(root, "Firmware binary input file", str(firmware_input_hex))
    _set_xml_param_value(root, "Firmware execution area offset", f"0x{exec_offset:X}")
    _set_xml_output_value(root, "Image output file", str(image_output_hex))

    # Write XML with proper formatting for TPC tool
    tree.write(output_xml, encoding="utf-8", xml_declaration=True, method="xml")
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
    parser.add_argument("--ap", default="1", help="SWD AP index")
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
            print(f"Programming merged HEX: {merged_hex}")

            # Reset, halt and program the hex file keeping the core halted afterwards
            assert_open_state(provision_connection, "provision start")
            hard_reset(provision_connection)
            halt_core(provision_connection)
            mass_erase(provision_connection)
            halt_core(provision_connection) # Just for sanity core shouldn't be running
            program_hex(provision_connection, merged_hex)

        # BOOT0 high for OBK provisioning stage.
        prompt_boot0_position(1)

        for obk in obk_files:
            print(f"Provisioning OBK via SDP: {obk}")
            program_obk(provision_connection, obk)

        # Return BOOT0 to normal boot position.
        prompt_boot0_position(0)

        # Verify one last time that we're still in OPEN state and halted.
        assert_open_state(provision_connection, "final verification")
        print("Provisioning completed with product state kept OPEN.")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
