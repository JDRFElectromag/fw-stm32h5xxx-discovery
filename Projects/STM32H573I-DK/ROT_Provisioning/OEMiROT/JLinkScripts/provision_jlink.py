import subprocess
import tempfile
from pathlib import Path

from intelhex import IntelHex

# Configuration
SCRIPT_DIR = Path(__file__).parent
JLINK_SCRIPTS_DIR = SCRIPT_DIR
OEMIROT_DIR = SCRIPT_DIR.parent
CUBE_FW_PATH = SCRIPT_DIR / "../../../../.."

DEVICE = "STM32H573IIKxQ"
INTERFACE = "SWD"
SPEED = "4000"

OEMIROT_BOOT_HEX = CUBE_FW_PATH / "Projects/STM32H573I-DK/Applications/ROT/OEMiROT_Boot/Binary/OEMiROT_Boot.hex"
ROT_TZ_S_APP_INIT_SIGN_HEX = CUBE_FW_PATH / "Projects/STM32H573I-DK/Applications/ROT/OEMiROT_Appli/Binary/rot_tz_s_app_init_sign.hex"
DA_OBKEY = OEMIROT_DIR / "../DA/Binary/DA_Config.obk" # Use the default debug access certs
OEMIROT_CONFIG_OBKEY = OEMIROT_DIR / "Binary/OEMiRoT_Config.obk" # Enc and auth keys default too. never updated them.

JLINK_EXE = "JLinkExe"
DEVPRO_EXE = "DevProExe"
DEVPRO_SCRIPT = "PCode_DevPro_ST_STM32H5.pex"

import subprocess

def subproc_run(cmd) -> str:
    process = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,  # line-buffered
    )

    output_lines = []

    for line in process.stdout:
        print(line, end="")  # real-time logging
        output_lines.append(line)

        if "error" in line.casefold():
            process.kill()
            raise RuntimeError("ERROR Found in JLINK script")

    process.wait()

    if process.returncode != 0:
        raise subprocess.CalledProcessError(process.returncode, cmd)

    return "".join(output_lines)

def run_jlink_script(script_name, action_str):
    script_path = Path(script_name)
    if not script_path.is_absolute():
        script_path = JLINK_SCRIPTS_DIR / script_path

    print(action_str)
    cmd = [
        JLINK_EXE,
        "-device", DEVICE,
        "-if", INTERFACE,
        "-speed", SPEED,
        "-autoconnect", "1",
        "-CommandFile", str(script_path)
    ]
    return subproc_run(cmd)

def generate_jlink_flash_script(output_dir, image_file, reset_board=False):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "reset" if reset_board else  "",
        "halt",
        f"loadfile {image_file}",
        "halt", # Must stay halted after this.
        "exit"
    ]
    script_path = output_dir / "flash_images.jlink"
    with open(script_path, 'w') as f:
        f.write('\n'.join(script_content))

    print(f"Generated flash programming script: {script_path}")
    return script_path


def merge_hex_images(boot_hex_file, app_hex_file, output_hex_file):
    for required_file in (boot_hex_file, app_hex_file):
        if not required_file.exists():
            raise FileNotFoundError(f"Missing required firmware image: {required_file}")



    print(f"Merged HEX generated: {output_hex_file}")


def run_devpro_operation(operation, config_vals=None) -> str:
    cmd = [
        DEVPRO_EXE,
        "-operation", operation,
        "-if", INTERFACE,
        "-speed", SPEED,
        "-ScriptFile", DEVPRO_SCRIPT,
    ]
    if config_vals:
        for key, value in config_vals.items():
            cmd.extend(["-SetConfigVal", f"{key}={value}"])
    return subproc_run(cmd)

def program_obkeys():
    # Option Byte Key
    print("Discovering product state...")
    run_devpro_operation("DbgAuthDiscover")

    obk_files = [
        DA_OBKEY,
        OEMIROT_CONFIG_OBKEY,
    ]

    for obk_file in obk_files:
        print(f"Provisioning OBK with DevPro: {obk_file}")
        run_devpro_operation("DbgAuthProvision", {"DataFile": str(obk_file)})

def write_ob(register_name: str, value: int) -> None:
    value_hex = f"0x{value:08X}"
    print(f"Writing option byte register: {register_name} = {value_hex}")
    run_devpro_operation(
        "WriteOptionBytes",
        {"OptionName": register_name, "Value": value_hex},
    )

def pack_start_end(start: int, end: int) -> int:
    return ((end & 0xFF) << 16) | (start & 0xFF)

def pack_secboot(lock: int, secbootadd: int) -> int:
    return ((lock & 0xFF) << 24) | (secbootadd & 0x00FFFFFF)

def program_option_bytes() -> None:
    # Program the min set of OB for bootpath to work.
    # Expect factory default option bytes to exist as
    # i don't program all values

    # This register control alot, including product state,
    # even though JLINK has a discrete command for product state
    # we can set it through this register. The setup is decoded below
    write_ob("FLASH_OPTSR", 0x2D30EDF8) # Factory default if I don't program this someone R2 doesn't stick. -_-

    """
    SRAM1_3_RST: Value: 0x00000001 -> SRAM1 and SRAM3 not erased when a system reset occurs
    SRAM3_ECC: Value: 0x00000001 -> SRAM3 ECC check disabled
    USBPD_DIS: Value: 0x00000000 -> Enabled
    SRAM2_RST: Value: 0x00000000 -> SRAM2 erased when a system reset occurs
    BKPRAM_ECC: Value: 0x00000001 -> BKPRAM ECC check disabled
    SRAM2_ECC: Value: 0x00000000 -> SRAM2 ECC check enabled
    TZEN: Value: 0x000000B4 -> TrustZone enabled
    """
    write_ob("FLASH_OPTSR2", 0xB4000034)

    # Configure secure watermark
    write_ob("FLASH_SECWM1R", pack_start_end(0x00, 0x17))
    write_ob("FLASH_SECWM2R", pack_start_end(0x7F, 0x00))

    # Final hardening: WRP + HDP + boot address
    write_ob("FLASH_WRP1R", 0xFFFFFFF8)
    write_ob("FLASH_WRP2R", 0xFFFFFFFF)

    write_ob("FLASH_HDP1R", pack_start_end(0x00, 0x13))
    write_ob("FLASH_HDP2R", pack_start_end(0x7F, 0x00))
    write_ob("FLASH_SECBOOTR", pack_secboot(0xB4, 0x0C0000)) #Address of secure boot + lock the register

def program_firmware():
    with tempfile.TemporaryDirectory(prefix="oemirot_flash_") as temp_dir:
        temp_path = Path(temp_dir)
        print(f"Merging {OEMIROT_BOOT_HEX.name} + {ROT_TZ_S_APP_INIT_SIGN_HEX.name}")
        boot_hex = IntelHex(str(OEMIROT_BOOT_HEX))
        app_hex = IntelHex(str(ROT_TZ_S_APP_INIT_SIGN_HEX))
        merged_hex = IntelHex()
        merged_hex.merge(boot_hex)
        merged_hex.merge(app_hex)
        merged_hex_path = temp_path / "merged_oemirot.hex"
        merged_hex.write_hex_file(str(merged_hex_path))

        # After this the baord core should never run
        script_path = generate_jlink_flash_script(output_dir=temp_path, image_file=merged_hex_path, reset_board=True)
        run_jlink_script(script_path, "Programming merge hex file...")


def main():
    # Use STCubeProgrammer to reset to factory defaults.
    # If device is provisioned already you better have password
    # or certicate to get Debugger access otherwise device is bricked
    # print("Expect a fresh device with all factory default values")

    input("Set BOOT0=0. Press Enter to continue...")

    print("Program Firmware")
    program_firmware()

    print("Program Option Bytes, but leave debugger access open")
    program_option_bytes()

    # To program OBK we need to move to PROVISIONING state
    print("Setting product state to PROVISIONING")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONING"})

    input("Set BOOT0=1. Press Enter to continue...")
    program_obkeys()
    print("OBK provisioning complete")

    input("Set BOOT0=0. To Boot from main flash and power cycle board")

    # At this point the bootloader should transitation the option bytes
    # to fianl most secure state as well as product state.
    # The debugger can't applies these all atomatically and some option byte
    # can cause the debugger to loose acccess as well as product state transition.
    # TODO test programming OB again for better lock down and settting ProdState alst


if __name__ == "__main__":
    main()
