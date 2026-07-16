# note; this script is only for initial provisioning.
#       we need to write a DFU module written (to load an new application into memory)
#           - we might need 2, or a script, etc. as we need to be able to load a new app in via JTAG/JLINK during development,
#             and via OTA.
#       we need an OTA module.
#
#####################
#
#       Initial Provisioning:
#           - full regression (chip erase)
#           - we load in the bootloader at this time (in this script!).
#           - bootloader is NOT signed or encrypted.
#           - we write in some secure keys.
#           - we do NOT create a DFU package for the appliation, DFU is only for UPGRADING the application in the future.
#           - we (force) write the initial applcation directly to flash, which includes an app header (at the top (see: APP_PRIMIARY_SLOT_HEADER in linker)) which
#               includes the signature for the application, and the starting address of the application, etc.
#               - this is written to slot 1 (DFU ALWAYS write to slot 2).
#               - note this application is signed, but not encrypted, using the ST Trusted packaged creator CLI).
#                   - see the Init_Code_Config XML file.
#
#       DFU: build a hex application.
#            sign and encrypt it (app header is added here by the tool:STM32TrustedPackageCreateor_CLI) (python scripts also exist: ..see path in slack)
#               - using the non-Init_code config (OEMiROT_S_Code_Image.xml)
#            via jlink or OTA
#                - load it into the SECONDARY slot of MCUboot, we do this using the MCUBOOT API.
#                   - write directly to the flash address of the secondar slot.
#                   - then tell mcu boot that there's an upgrade available (mcuboot: boot utilies)
#                       - see slack wiki page.
#           - in the application layer, we need a common block that checks the health of the application.
#               - mcuBoot: boot_set_confirmed().
#               -our application needs to call this if we think all is well, and this marks the image as stable, so
#                mcu boot wont revert to the previous slot on next boot.
#               - we only need to set this flag if it's different that what's in flash. (don't wear out flash)!
#               - check if boot_set_confimed() only writes to flash if it's different that the state you want to write.
#
#           DFU process has been somewhat verified via bit twiddling (jtag/jlink), but not with explicit code.
#               - it would be necessary project, to build "blinky2" (different blink rate), and load it.
#
#####################
#
#   JTAG PORT:
#       Once the processor has been provisioned (i.e. secured and closed) the JTAG port
#       is locked out (although we control "how much" it's locked out.
#       Unlike the STM32L4 (51) we can "close" the JTAG port without "locking" it out.
#       Locked = unrecoverable.
#       Closed = recoverable (open-able) with a security certificate.
#
#####################
#
#   DFU:
#       Creating a DFU Package:

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

# Ensure xml matches the map file for application
# Consumed everytime the script runs.
# Required to created the SIGNED version of the hex file.
# Should be made modifable as certain fields need to be dynamically updated after the build,
#  based on the corresponding map file. (<- python scripting)
APP_INIT_IMG_CONFGS = "/home/rlaswick/repos/fw-stm32h5xxx-discovery/Projects/STM32H573I-DK/ROT_Provisioning/OEMiROT/Images/OEMiROT_S_Code_Init_Image.xml"
APP_INIT_IMG_CONFGS = Path(APP_INIT_IMG_CONFGS)

# Absolute path required.
OEMIROT_BOOT_HEX = "/home/rlaswick/repos/fw-thor/appProcessor/bootloader/mcuboot/build/debug/stm32h573i-dk/autonomySensor_mcuboot_sec_stm32h573i-dk.hex"
OEMIROT_BOOT_HEX = Path(OEMIROT_BOOT_HEX)

# Signed application image with header
# New hex file, that includes the applciation header that's been signed.
ROT_TZ_S_APP_INIT_SIGN_HEX = "/home/rlaswick/repos/fw-thor/appProcessor/applications/blinky/build/debug/stm32h573i-dk/with_mcuboot/autonomySensor_blinky_with_mcuboot_sec_signed_stm32h573i-dk.hex"
ROT_TZ_S_APP_INIT_SIGN_HEX = Path(ROT_TZ_S_APP_INIT_SIGN_HEX)

# STM Trusted Package creator takes in XML and generates these OBK files.
# These 3 obk are development (we can use these default STM files, or create our own).
# We need 3 new ones production builds.
# There are matching XML files for each of these.
# We would modifiy them and feed them to the Trusted Package Createor to generate new OBKs.
# these only need to be generated ONCE, once for dev and once for production.
DA_OBKEY = OEMIROT_DIR / "../DA/Binary/DA_Config.obk" # Use the default debug access certificates.
OEMIROT_CONFIG_OBKEY = OEMIROT_DIR / "Binary/OEMiRoT_Config.obk" # Encryption and authentication keys use defaults and were never updated.
OEMIROT_DATA_OBKEY = OEMIROT_DIR / "Binary/OEMiRoT_Data.obk" # Not used directly, but must be programmed or hash checks fail.

# eventually, this secure key and certificate need to be control (fw-thor? azure key vault?).
# private key = SK
# public key = PK
# NOTE: this key and certificate are the default ones provided by ST. We'll want our own.
DEBUGGER_ACCESS_ROOT_DIR = CUBE_FW_PATH / "Projects/STM32H573I-DK/ROT_Provisioning/DA"
DEBUGGER_ACCESS_SK = DEBUGGER_ACCESS_ROOT_DIR / "Keys/key_1_root.pem"
DEBUGGER_ACCESS_CERT = DEBUGGER_ACCESS_ROOT_DIR / "Certificates/cert_root.b64"

JLINK_EXE = "JLinkExe"
DEVPRO_EXE = "DevProExe" # Another JLink exe, that's needed for security stuff.
DEVPRO_SCRIPT = "PCode_DevPro_ST_STM32H5.pex" # provided by JLink (included in the latest standard jlink download).
                                              # pex is an actual program! jlink puts code into ram, and runs it.
                                              # because the debugger needs the cpu to execute certain secuirty APIs / protocols.
STM32_PROGRAMMER_CLI_EXE = "STM32_Programmer_CLI"   # this shouldn't be needed, but jlink by itself doesn't work fully/reliably with just jlink.
                                                    # the stm programmer is FAR more stable/relible when it comes to writing option bytes.
                                                    # speciically when writing the the SECBOOT_LOCK byte
CPU_HALTED_LOG_LINE = "CPU halted."
HALT_WAIT_TIMEOUT_S = 30 # randon time, any time could be picked. Waiting for teh cpu to actually halt itself. IMPORTANT.


# fancy / helper routine to run a sub process
# prints stdout and stderro the the screen
# aborts on error logs in scripts.
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

    # this callback is required to keep the JLINK process open,
    # so that the processor doesn't reset once the JLINK process ends.
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


def generate_jlink_dump_first_32_bytes_script(output_dir):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "halt",
        "mem8 0x08000000, 32",
        "exit",
    ]

    script_path = output_dir / "dump_first_32_bytes.jlink"
    with open(script_path, 'w') as f:
        f.write('\n'.join(script_content))

    print(f"Generated J-Link dump script: {script_path}")
    return script_path


def dump_first_32_bytes_at_flash_base():
    with tempfile.TemporaryDirectory(prefix="dump_flash_32_bytes_") as temp_dir:
        script_path = generate_jlink_dump_first_32_bytes_script(output_dir=Path(temp_dir))
        return run_jlink_script(script_path, "Dumping first 32 bytes at 0x08000000...")


def generate_jlink_dump_ram_first_32_bytes_script(output_dir):
    output_dir = Path(output_dir)
    script_content = [
        "connect",
        "halt",
        "mem8 0x20000000, 32",
        "exit",
    ]

    script_path = output_dir / "dump_ram_first_32_bytes.jlink"
    with open(script_path, 'w') as f:
        f.write('\n'.join(script_content))

    print(f"Generated J-Link RAM dump script: {script_path}")
    return script_path


def dump_first_32_bytes_at_ram_base():
    with tempfile.TemporaryDirectory(prefix="dump_ram_32_bytes_") as temp_dir:
        script_path = generate_jlink_dump_ram_first_32_bytes_script(output_dir=Path(temp_dir))
        return run_jlink_script(script_path, "Dumping first 32 bytes at 0x20000000...")


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


# a very handy/useful way to view the option bytes in memory,
# is to use the ST Cube Programmer, and use the OB section.
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

    # 0xC0000 --> Bootloader secure boot address. Must match what we plan to flash or flashing will fail.
    # IMPORTANT!   0xC3 --> Leave it unlocked. otherwise can't flash bootloader or watermarks
    write_ob("FLASH_SECBOOTR", pack_secboot(0xC3, 0xC0000))

    #write_ob("FLASH_SECWM1R", pack_start_end(0x00, 0x13))
    #write_ob("FLASH_SECWM2R", pack_start_end(0x7F, 0x00))
    write_ob("FLASH_SECWM1R", pack_start_end(0x00, 0x7f))
    write_ob("FLASH_SECWM2R", pack_start_end(0x00, 0x04))

def program_option_bytes_step2():
    print(inspect.currentframe().f_code.co_name)
    write_ob("FLASH_WRP1R", 0xFFFFFFFC) # water marks.  we'll probably need to ajust these if the linker script or map file changes.
    write_ob("FLASH_WRP2R", 0xFFFFFFFF)

    write_ob("FLASH_HDP1R", pack_start_end(0x00, 0x0F))
    write_ob("FLASH_HDP2R", pack_start_end(0x7F, 0x00))

def program_option_bytes_secure_boot_lock():
    print(inspect.currentframe().f_code.co_name)

    # Need to lock the SECBOOT register for the MCU to boot properly.
    # Doing this from J-Link is flaky, regardless of boot0 pin.
    # It mostly doesn't work as you can write it and it says successful
    # but reading it back show that is wrong.
    #
    # write_ob("FLASH_SECBOOTR", pack_secboot(0xB4, 0xC0000))

    # Using JLINK and STM32 cube programmer flashing it makes it work.
    # Unsure why maybe STLINK is using there own ram loaders
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

# write the application to flash, THEN
# write the boot loader to flash, THEN
# note: we could merge the 2, and just write 1 hex file.
# note: the processor MUST not be allowed to run until both images have been flashed AND
#       ALL of the provision steps have completed.
# note: This routine HALTS the cpu.
# ntoe: JLINK script is still running in a background thread.
#       (meaning that the jlink if is still open.  remember, closing the jlink program will force reset the cpu
#        and we don't want that!!)
def program_firmware():
    with tempfile.TemporaryDirectory(prefix="oemirot_flash_") as temp_dir:
        temp_path=Path(temp_dir)

        # Ensure that bootloader flashed last and NEVER RUN!! CPU must stay halted always

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
    validate_secbootr(0x0C0000C3) # not necessarily needed, but it's a read back check.
                                  # desmond was having issues at some point, so this was a check he added.

def main():
    # Open a locked JTAG port
    if 0:
        debugger_open_intrusive_level3()
        # dump_first_32_bytes_at_flash_base()
        # dump_first_32_bytes_at_ram_base()
        return

    # Perform a full device regression (chip erase).
    if 0:
        try:
            full_regression()
            mass_erase()
        except Exception as e:
            print("MCU Power Cycle required. Do full power down for 3 second and power up and wait 3 seconds")
            return

    # Inject the header with signatures. mcuboot has python script to do this too.
    # this takes the `west build` hex file and generates the "real" hex file that we're actually going to write to flash.
    subproc_run(["STM32TrustedPackageCreator_CLI", "-pb", str(APP_INIT_IMG_CONFGS)])


    ###
    # The next few steps REQUIRE the physical manuipulate of a GPIO pin (BOOT0),
    # for headless (human less) provisioning.
    #
    # Note: a full hard power cycle is reuired to full regress a chip,
    # the thought is that a human would do this physcialy i fthis needed to
    # be done.
    ##


    # If with_bootloader.ld updates then map file has new address
    # this means we need to update option byte too. Bootloader should
    # tell you waht ened updating.

    input("Set BOOT0=0. Press Enter to continue...")

    # Option bytes must be set first; otherwise address mapping will be wrong.
    # TZEN=1 will cause a remap of flash.
    # You also need to set the secure boot watermark at this stage.
    # Doing it later causes issues.
    # --
    # Step 1 is required to enable the trust zone so the next step (code loading)
    # can be loaded into the secure area of flash, and not the default non-secure area.
    program_option_bytes_step1_with_secbootr_validations()

    # SECBOOTR needs to be set with the address we plan to program
    # the bootloader into as well as UNLOCK byte.
    # Without this bootlaoder programming will fail.
    stop_bootloader_hold_thread = program_firmware()
    # cpu is halted.

    # Even when trying to keep the CPU halted while DevProExe runs,
    # sometimes the CPU unhalts and the bootloader runs. As DevProExe
    # and JLINK comander are 2 different programs.
    # To get around this switch the BOOT0 pin before we start devProExe tool.
    # This ensure that when the DevProExe tool does start to flash the OB
    # the bootloader doesn't run.
    #---
    # note: now that the bootloader and applciation is loaded into flash,
    #       we need to boot into SYSMEM  (system flash? ST ROM CODE)
    #       so the security peripherals can run.
    #       We're actually booting into STiROT bootloader (OUR CODE we just flash WILL NOT RUN NOW, which is a good thing).
    #       Root secure services can only be accessed in this BOOT0=1 mode.
    input("Set BOOT0=1. Press Enter to continue...")

    # allow the JLINK thread to close, which will reset the cpu.
    # we no longer need to prevent the cpu from resetting/running, so we can
    # close the JLINK thread moving forward.
    stop_bootloader_hold_thread()

    # We can flash OBs when BOOT0=1. MCU boot won't be runnng
    # as CPU is in ROM flash. So we don't run nto any issue.
    # FYI if you leave BOOT=0 and do this it will not complain
    # it may even look like it worked this only happens if
    # OBK already has the correct keys. It only looks like it worked
    # becasue OBK was already provisioned.
    # --
    # Hide the bootloader memory space.
    program_option_bytes_step2() # part 1: this can be done with Jlink
    program_option_bytes_secure_boot_lock() # part 2: this part has to be done with the ST programmer!
    # it might be worth while reporting this bug to JLINK

    # OBK can only be programmed in PROVISIONING state!!!
    # Even the datasheet says this.
    # --
    # We still don't want the cpu to run yet, as no secure keys have been loaded.
    # We now need to put the processor into PROVISIONING state.
    # --
    # We were in the OPEN state prevously.
    print("Setting product state to PROVISIONING")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONING"})

    # Actually write the 3 OBK keys/files into the processor.
    # Root secure services puts these keys where they need to be.
    program_obkeys()

    # MCU will not boot in PROVISIONING you must transition
    # to any state > PROVISIONING. Just don't use LOCK state.
    print("Setting product state to PROVISIONED")
    run_devpro_operation("SetDeviceState", {"ProdState": "PROVISIONED"})
    # --
    # we might want to be in the CLOSED state for production builds,
    # but PROVISIONED is likely acceptable for devleopment builds.

    # we want to soft reset here, but ensure the POR subsystem is hit, so
    # use the RESET button on the dev kit.
    # JLINK has a reset config flag so it's reset command can be behave differently.
    # Here we want the user to change BOOT0 to 0, the hit the reset button.
    # We'll have to provide an option for this on our JDRF boards.
    # A hard reset might be the solution here.
    input("Set BOOT0=0. Hard reset")
    # reset_mcu()

    # uart_run_term(port="/dev/ttyACM0")

if __name__ == "__main__":
    main()
