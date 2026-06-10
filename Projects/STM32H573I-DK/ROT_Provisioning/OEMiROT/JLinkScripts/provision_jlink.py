import re
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

def subproc_run(cmd) -> str:
    result = subprocess.run(
        cmd,
        check=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.stdout:
        print(result.stdout)
        return result.stdout
    else:
        return ""

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

def generate_jlink_flash_script(output_dir, image_file):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "reset",
        "halt",
        f"loadfile {image_file}",
        "exit",
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

    # State required to program OBKs can't do it in OPEN and other state
    # debugger can't access things.
    print("Setting product state to PROVISIONING")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONING"})

    obk_files = [
        DA_OBKEY,
        OEMIROT_CONFIG_OBKEY,
    ]

    for obk_file in obk_files:
        print(f"Provisioning OBK with DevPro: {obk_file}")
        run_devpro_operation("DbgAuthProvision", {"DataFile": str(obk_file)})

def program_ob():
    # Option Bytes. DO NOT MIXUP with OBK (ST bad at naming stuff)
    # This just the default OB + min changes needed to use the OEMiROT boot path.
    # My intention here is not to explian each bit just read the refManual or use
    # STMCubeMX tool to understand each.
    ob_config = {
        #
        "FLASH_OPTSR": "0xB4FF00FF", # Flash Option Status Register (main control) TZEN=1
        "FLASH_OPTSR2": "0xC0000000", # Flash Option Status Register 2
        "FLASH_SECWM1R": "0x00170000", # Security Watermark 1 for Bank 1
         "FLASH_SECWM2R": "0x0000007F", # Security Watermark 2 for Bank 2
        "FLASH_NSBOOTR": "0xFFFFFFF8", # Non-Secure Boot Register, we have no NS app running.
        "FLASH_SECBOOTR": "0xFFFFFFFF", # Secure Boot Register
        "FLASH_WRP1R": "0x00130000", # Write Protection Register 1 for Bank 1
        "FLASH_WRP2R": "0x0000007F", # Write Protection Register 2 for Bank 2
        "FLASH_OTPBLR": "0xB4FF00FF", # OTP Block Lock Register
        "FLASH_HDP1R": "0xED0000FF", #  Hidden Debug Port Bank 1
    }

    for option_name, value in ob_config.items():
        print(f"Writing option byte: {option_name} = {value}")
        run_devpro_operation("WriteOptionBytes", {"OptionName": option_name, "Value": value})

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

        script_path = generate_jlink_flash_script(output_dir=temp_path, image_file=merged_hex_path)
        run_jlink_script(script_path, "Programming merge hex file...")


def main():
    input("Set BOOT0=1. Press Enter to continue...")
    program_obkeys()
    print("OBK provisioning complete")

    input("Set BOOT0=0. Press Enter to continue...")
    program_firmware()

    print("Program Option Bytes")
    program_ob()

    print("Setting product state to OPEN")
    run_devpro_operation("SetDeviceState", {"ProdState": "OPEN"})

if __name__ == "__main__":
    main()
