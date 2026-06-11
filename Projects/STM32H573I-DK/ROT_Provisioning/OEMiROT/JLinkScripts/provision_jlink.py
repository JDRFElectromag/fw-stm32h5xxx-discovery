import inspect
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

def write_ob(register_name: str, value: int):
    value_hex = f"0x{value:08X}"
    print(f"Writing option byte register: {register_name} = {value_hex}")
    run_devpro_operation(
        "WriteOptionBytes",
        {"OptionName": register_name, "Value": value_hex},
    )

def read_ob(register_name: str):
    print(f"Read option byte register: {register_name}")
    run_devpro_operation(
        "ReadOptionBytes",
        {"OptionName": register_name},
    )

def pack_start_end(start: int, end: int) -> int:
    return ((end & 0xFF) << 16) | (start & 0xFF)

def pack_secboot(lock: int, secbootadd: int) -> int:
    return ((secbootadd & 0x00FFFFFF) << 8) | (lock & 0xFF)

def program_option_bytes_step1():
    print(inspect.currentframe().f_code.co_name)
    """
    SRAM1_3_RST: Value: 0x00000001 -> SRAM1 and SRAM3 not erased when a system reset occurs
    SRAM3_ECC: Value: 0x00000001 -> SRAM3 ECC check disabled
    USBPD_DIS: Value: 0x00000000 -> Enabled
    SRAM2_RST: Value: 0x00000000 -> SRAM2 erased when a system reset occurs
    BKPRAM_ECC: Value: 0x00000001 -> BKPRAM ECC check disabled
    SRAM2_ECC: Value: 0x00000000 -> SRAM2 ECC check enabled
    TZEN: Value: 0x000000B4 -> TrustZone enabled
    """
    # Trust zone affect flash mapping. So we must enable it first.
    # Otherwise you will likely be programming NS zones.
    write_ob("FLASH_OPTSR2", 0xB4000034)

    # To write secure flash watermarks (FLASH_SECWMxR) we must program
    # the secure boot register but it must be left unlocked.
    # 0xC0000 --> bootloader secure zone start address
    # 0xCE --> Leave it unlocked.
    write_ob("FLASH_SECBOOTR", pack_secboot(0xC3, 0xC0000))

    write_ob("FLASH_SECWM1R", pack_start_end(0x00, 0x17))
    write_ob("FLASH_SECWM2R", pack_start_end(0x7F, 0x00))

def program_option_bytes_step2():
    print(inspect.currentframe().f_code.co_name)
    write_ob("FLASH_WRP1R", 0xFFFFFFF8)
    write_ob("FLASH_WRP2R", 0xFFFFFFFF)

    write_ob("FLASH_HDP1R", pack_start_end(0x00, 0x13))
    write_ob("FLASH_HDP2R", pack_start_end(0x7F, 0x00))

    # Need to lock the secure boot address otherwise MCU won't boot
    write_ob("FLASH_SECBOOTR", pack_secboot(0xB4, 0xC0000))

def read_program_option_bytes():
    read_ob("FLASH_OPTSR")
    read_ob("FLASH_OPTSR2")
    read_ob("FLASH_NSBOOTR")
    read_ob("FLASH_SECBOOTR")
    read_ob("FLASH_SECWM1R")
    read_ob("FLASH_SECWM2R")
    read_ob("FLASH_WRP1R")
    read_ob("FLASH_WRP2R")
    read_ob("FLASH_OTPBLR")
    read_ob("FLASH_EDATA1R")
    read_ob("FLASH_EDATA2R")
    read_ob("FLASH_HDP1R")
    read_ob("FLASH_HDP2R")

def program_firmware():
    print(inspect.currentframe().f_code.co_name)
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

    program_option_bytes_step1()
    program_firmware()
    program_option_bytes_step2()

    # OBK can only be programmed in this state!!!
    # Even the datasheet says.
    # ST provisioning scripts with cube programmer
    # has a flow where it looks like OBK is provisioning
    # in OPEN state the MCU stays open but I don't know how
    # they are managing to do this. As if you move PROVISIONING --> OPEN
    # the MCU erases. JLINK doesn't even allow you to this transition.
    # if you try to do it via `FLASH_OPTSR2` the MCU auto erased.
    print("Setting product state to PROVISIONING")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONING"})

    input("Set BOOT0=1. Press Enter to continue...")
    program_obkeys()
    print("OBK provisioning complete")

    # MCU won't boot in PROVISIONING need to transition out of it.
    # JLINK does not provide a feature to transition back to OPEN
    # as this would trigger the MCU to erase. I have no clue how ST
    # is managing to program OBK in provisioning state unless they
    # are performing hidden actions in the programmer.
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONED"})


if __name__ == "__main__":
    main()
