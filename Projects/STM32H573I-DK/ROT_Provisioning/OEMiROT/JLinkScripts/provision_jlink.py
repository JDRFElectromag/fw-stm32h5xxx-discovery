import inspect
import re
import subprocess
import tempfile
import threading
from typing import Callable
from pathlib import Path
import time

from intelhex import IntelHex
from uart_terminal import run_term as uart_run_term

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
DA_OBKEY = OEMIROT_DIR / "../DA/Binary/DA_Config.obk" # Use the default debug access certificates.
OEMIROT_CONFIG_OBKEY = OEMIROT_DIR / "Binary/OEMiRoT_Config.obk" # Encryption and authentication keys use defaults and were never updated.
OEMIROT_DATA_OBKEY = OEMIROT_DIR / "Binary/OEMiRoT_Data.obk" # Not used directly, but must be programmed or hash checks fail.

DEBUGGER_ACCESS_ROOT_DIR = CUBE_FW_PATH / "Projects/STM32H573I-DK/ROT_Provisioning/DA"
DEBUGGER_ACCESS_SK = DEBUGGER_ACCESS_ROOT_DIR / "Keys/key_1_root.pem"
DEBUGGER_ACCESS_CERT = DEBUGGER_ACCESS_ROOT_DIR / "Certificates/cert_root.b64"

JLINK_EXE = "JLinkExe"
DEVPRO_EXE = "DevProExe"
DEVPRO_SCRIPT = "PCode_DevPro_ST_STM32H5.pex"
STM32_PROGRAMMER_CLI_EXE = "STM32_Programmer_CLI"
CPU_HALTED_LOG_LINE = "CPU halted."
HALT_WAIT_TIMEOUT_S = 30

def subproc_run(
    cmd,
    on_output_line: Callable[[str], None] | None = None,
    on_process_start: Callable[[subprocess.Popen], None] | None = None,
    error_watch_terms = ["error"],
    error_ignore_terms = [],
) -> str:
    error_watch_terms_cf = [term.casefold() for term in error_watch_terms]
    error_ignore_terms_cf = [term.casefold() for term in error_ignore_terms]

    process = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,  # line-buffered
    )

    if on_process_start is not None:
        on_process_start(process)

    output_lines = []

    for line in process.stdout:
        print(line, end="")  # real-time logging
        output_lines.append(line)
        if on_output_line is not None:
            on_output_line(line)

        line_cf = line.casefold()
        has_watched_error = any(term in line_cf for term in error_watch_terms_cf)
        has_ignored_error = any(term in line_cf for term in error_ignore_terms_cf)

        if has_watched_error and not has_ignored_error:
            process.kill()
            raise RuntimeError("ERROR Found in JLINK script")

    process.wait()

    if process.returncode != 0:
        raise subprocess.CalledProcessError(process.returncode, cmd)

    return "".join(output_lines)

def run_jlink_script(
    script_name,
    action_str,
    on_output_line: Callable[[str], None] | None = None,
    on_process_start: Callable[[subprocess.Popen], None] | None = None,
):
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
    return subproc_run(
        cmd,
        on_output_line=on_output_line,
        on_process_start=on_process_start,
    )

def generate_jlink_reset_script(output_dir):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "reset",
        "exit"
    ]
    script_path = output_dir / "flash_images.jlink"
    with open(script_path, 'w') as f:
        f.write('\n'.join(script_content))
    return script_path

def generate_jlink_erase_script(output_dir):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "reset",
        "erase",
        "exit"
    ]
    script_path = output_dir / "flash_images.jlink"
    with open(script_path, 'w') as f:
        f.write('\n'.join(script_content))
    return script_path

def generate_jlink_flash_script(output_dir, image_file, is_hold_halt=False):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "halt", # Do not reset here.
        f"loadfile {image_file}",
        "halt", # Must remain halted after this.
    ]
    if is_hold_halt:
        script_content.append("WaitHalt")
    else:
        script_content.append("exit")

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


def run_stm32_programmer_cli(args=None, connection=None) -> str:
    cmd = [STM32_PROGRAMMER_CLI_EXE]

    # Default connection for ST-LINK/J-LINK based OB programming from CLI.
    if connection is None:
        connection = {
            "port": "JLINK",
            "speed": "reliable",
            "ap": "0",
            "mode": "Hotplug",
        }

    connect_kv = " ".join(f"{k}={v}" for k, v in connection.items())
    cmd.extend(["-c", connect_kv])

    if args:
        cmd.extend(args)

    return subproc_run(
        cmd,
        # This error appears frequently when using the J-Link debugger.
        error_ignore_terms=["error: st-link interface not available"],
    )

def program_obkeys():
    print(inspect.currentframe().f_code.co_name)
    print("Discovering product state...")
    run_devpro_operation("DbgAuthDiscover")

    obk_files = [
        DA_OBKEY,
        OEMIROT_CONFIG_OBKEY,
        OEMIROT_DATA_OBKEY,
    ]

    for obk_file in obk_files:
        print(f"Provisioning OBK with DevPro: {obk_file}")
        run_devpro_operation("DbgAuthProvision", {"DataFile": str(obk_file)})

def _write_ob(register_name: str, value: int):
    value_hex = f"0x{value:08X}"
    print(f"Writing option byte register: {register_name} = {value_hex}")
    run_devpro_operation(
        "WriteOptionBytes",
        {"OptionName": register_name, "Value": value_hex},
    )

def write_ob(register_name: str, value: int):
    _write_ob(register_name, value)
    # time.sleep(0.1)

def read_ob(register_name: str):
    print(f"Read option byte register: {register_name}")
    return run_devpro_operation(
        "ReadOptionBytes",
        {"OptionName": register_name},
    )

def run_in_daemon_thread(func, args=(), kwargs=None):
    """Run a function in a daemon thread that dies if parent dies."""
    if kwargs is None:
        kwargs = {}
    thread = threading.Thread(target=func, args=args, kwargs=kwargs, daemon=True)
    thread.start()
    return thread

def parse_flash_secbootr_value(log_text: str):
    match = re.search(
        r"J-Link log:\s+FLASH_SECBOOTR\s+value:\s+(0x[0-9A-Fa-f]+)",
        log_text,
    )
    if not match:
        return None
    return int(match.group(1), 16)

def debug_access_auth_with_cert(perm: str):
    run_devpro_operation(
        "DbgAuthCert",
        {
            "CertFile": str(DEBUGGER_ACCESS_CERT),
            "KeyFile": str(DEBUGGER_ACCESS_SK),
            "Perm": perm
        },
    )

def full_regression():
    debug_access_auth_with_cert(perm="Full Regression")

def debugger_open_intrusive_level3():
    debug_access_auth_with_cert(perm="Level 3 Intrusive Debug")

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
    # TrustZone affects flash mapping, so it must be enabled first.
    # Otherwise you will likely be programming NS zones.
    write_ob("FLASH_OPTSR2", 0xB4000034)

    # To write secure flash watermarks (FLASH_SECWMxR) we must program
    # the secure boot register but it must be left unlocked.
    # 0xC0000 --> Bootloader secure boot address. Must match what we plan to flash or flashing will fail.
    # 0xC3 --> Leave it unlocked.
    write_ob("FLASH_SECBOOTR", pack_secboot(0xC3, 0xC0000))

    write_ob("FLASH_SECWM1R", pack_start_end(0x00, 0x17))
    write_ob("FLASH_SECWM2R", pack_start_end(0x7F, 0x00))

def program_option_bytes_step2():
    print(inspect.currentframe().f_code.co_name)
    write_ob("FLASH_WRP1R", 0xFFFFFFF8)
    write_ob("FLASH_WRP2R", 0xFFFFFFFF)

    write_ob("FLASH_HDP1R", pack_start_end(0x00, 0x13))
    write_ob("FLASH_HDP2R", pack_start_end(0x7F, 0x00))

def program_option_bytes_step3():
    print(inspect.currentframe().f_code.co_name)

    # Need to lock the SECBOOT register for the MCU to boot properly.
    # Doing this from J-Link is flaky, and it often fails.
    # It reports success, but readback can still be wrong.
    # write_ob("FLASH_SECBOOTR", pack_secboot(0xB4, 0xC0000))

    run_stm32_programmer_cli(args=["-ob", "SECBOOT_LOCK=0xB4"])

def program_option_bytes_defaults():
    print(inspect.currentframe().f_code.co_name)

    write_ob("FLASH_OPTSR2", 0xB4000034)
    write_ob("FLASH_SECBOOTR", pack_secboot(0xC3, 0))
    write_ob("FLASH_SECWM1R", pack_start_end(0x01, 0x00))
    write_ob("FLASH_SECWM2R", pack_start_end(0x01, 0x00))
    write_ob("FLASH_HDP1R", pack_start_end(0x01, 0x00))
    write_ob("FLASH_HDP2R", pack_start_end(0x01, 0x00))

    # Remove write protection.
    write_ob("FLASH_WRP1R", 0xFFFFFFFF)
    write_ob("FLASH_WRP2R", 0xFFFFFFFF)

def read_program_option_bytes():
    log = ""
    log += read_ob("FLASH_OPTSR")
    log += read_ob("FLASH_OPTSR2")
    log += read_ob("FLASH_NSBOOTR")
    log += read_ob("FLASH_SECBOOTR")
    log += read_ob("FLASH_SECWM1R")
    log += read_ob("FLASH_SECWM2R")
    log += read_ob("FLASH_WRP1R")
    log += read_ob("FLASH_WRP2R")
    log += read_ob("FLASH_OTPBLR")
    log += read_ob("FLASH_EDATA1R")
    log += read_ob("FLASH_EDATA2R")
    log += read_ob("FLASH_HDP1R")
    log += read_ob("FLASH_HDP2R")

    return log

def program_firmware():
    with tempfile.TemporaryDirectory(prefix="oemirot_flash_") as temp_dir:
        temp_path=Path(temp_dir)

        # Do not merge these HEX files. The bootloader must always be flashed last.
        # The ST provisioning script enforces this sequence too.

        script_path = generate_jlink_flash_script(output_dir=temp_path, image_file=str(ROT_TZ_S_APP_INIT_SIGN_HEX))
        run_jlink_script(script_path, "Programming App...")

        script_path = generate_jlink_flash_script(output_dir=temp_path, image_file=str(OEMIROT_BOOT_HEX), is_hold_halt=True)
        cpu_halted_event = threading.Event()
        stop_bootloader_event = threading.Event()
        bootloader_error = []
        bootloader_process_holder = {"process": None}

        def flash_bootloader_and_hold_mcu_in_reset():
            try:
                run_jlink_script(
                    script_path,
                    "Programming Bootloader...",
                    on_output_line=lambda line: cpu_halted_event.set() if CPU_HALTED_LOG_LINE in line else None,
                    on_process_start=lambda process: bootloader_process_holder.update({"process": process}),
                )
            except Exception as exc:
                if not stop_bootloader_event.is_set():
                    bootloader_error.append(exc)
                    cpu_halted_event.set()

        bootloader_thread = run_in_daemon_thread(flash_bootloader_and_hold_mcu_in_reset)

        if not cpu_halted_event.wait(timeout=HALT_WAIT_TIMEOUT_S):
            raise TimeoutError(
                f"Timed out after {HALT_WAIT_TIMEOUT_S}s waiting for '{CPU_HALTED_LOG_LINE}' in J-Link output"
            )

        if bootloader_error:
            raise RuntimeError("Bootloader flash thread failed before CPU halt confirmation") from bootloader_error[0]

        print("Finish programming and holding MCU halted")

        def stop_bootloader_hold_thread():
            stop_bootloader_event.set()
            process = bootloader_process_holder["process"]

            if process is not None and process.poll() is None:
                print("Stopping bootloader hold J-Link session...")
                process.terminate()
                try:
                    process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait(timeout=5)

            bootloader_thread.join(timeout=1)

        return stop_bootloader_hold_thread

def reset_mcu():
    print(inspect.currentframe().f_code.co_name)
    with tempfile.TemporaryDirectory(prefix="reset_mcu_") as temp_dir:
        script_path = generate_jlink_reset_script(output_dir=Path(temp_dir))
        run_jlink_script(script_path, "Resetting MCU...")

def mass_erase():
    print(inspect.currentframe().f_code.co_name)
    with tempfile.TemporaryDirectory(prefix="mass_erase") as temp_dir:
        script_path = generate_jlink_erase_script(output_dir=Path(temp_dir))
        run_jlink_script(script_path, "mass erasing...")

def validate_secbootr(expected):
    log = read_ob("FLASH_SECBOOTR")
    val = parse_flash_secbootr_value(log)
    if val != expected:
        raise RuntimeError(f"Bad secbootr. Got:{hex(val)}, expected: {hex(expected)}")

def program_option_bytes_step1_with_secbootr_validations():
    program_option_bytes_step1()
    validate_secbootr(0x0C0000C3)

def main():
    # try:
    #     full_regression() # only work if device was >= PROVISIONED
    # finally:
    #     mass_erase()
    # return

    input("Set BOOT0=0. Press Enter to continue...")

    # Option bytes must be set first; otherwise address mapping will be wrong.
    # TZEN=1 will cause a remap of flash.
    # You also need to set the secure boot watermark at this stage.
    # Doing it later causes issues.
    program_option_bytes_step1_with_secbootr_validations()

    # Program firmware WHILE SECBOOTR is UNLOCKED (0xC3)
    # J-Link needs to erase sectors, which is blocked if SECBOOTR is locked (0xB4)
    stop_bootloader_hold_thread = program_firmware()

    # Even when trying to keep the CPU halted while DevProExe runs,
    # sometimes the CPU unhalts and the bootloader runs.
    # That can prevent option bytes from being updated and leave the CPU
    # in a state where it cannot boot because OB updates are incomplete.
    # So we switch the boot mode right after flashing to prevent
    # the CPU from running the bootloader, then program the option bytes.
    input("Set BOOT0=1. Press Enter to continue...")
    stop_bootloader_hold_thread()

    # MCU is halted here. Now lock SECBOOTR while still halted to prevent firmware
    # from modifying it during early boot.
    program_option_bytes_step2()
    program_option_bytes_step3()

    # OBK can only be programmed in PROVISIONING state!!!
    # Even the datasheet says this.
    print("Setting product state to PROVISIONING")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONING"})

    program_obkeys()

    # MCU will not boot in PROVISIONING you must transition
    # to any state > PROVISIONING. Just don't use LOCK state.
    # print("Setting product state to PROVISIONED")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONED"})

    input("Set BOOT0=0. Hard reset")

    # reset_mcu()
    # uart_run_term(port="/dev/ttyACM0")

if __name__ == "__main__":
    main()
