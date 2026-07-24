from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


CLI = "STM32_Programmer_CLI"


def run_cmd(args: list[str], *, check: bool = True) -> subprocess.CompletedProcess[str]:
    print("+", " ".join(args))
    proc = subprocess.run(args, text=True, capture_output=True)
    if proc.stdout:
        print(proc.stdout, end="")
    if proc.stderr:
        print(proc.stderr, end="", file=sys.stderr)

    if check and proc.returncode != 0:
        raise RuntimeError(f"Command failed with exit code {proc.returncode}")
    return proc


def build_connection_arg(speed: str, ap: str, mode: str) -> str:
    return f"port=SWD speed={speed} ap={ap} mode={mode}"


def detect_open_state(connection: str) -> bool:
    proc = run_cmd([CLI, "-c", connection, "-ob", "displ"], check=False)
    out = (proc.stdout or "").upper()
    return "PRODUCT_STATE" in out and "OPEN" in out


def resolve_default_obk_files(script_dir: Path) -> list[Path]:
    return [
        (script_dir / "../DA/Binary/DA_Config.obk").resolve(),
        (script_dir / "Binary/OEMiRoT_Config.obk").resolve(),
        (script_dir / "Binary/OEMiRoT_Data.obk").resolve(),
    ]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--speed", default="reliable")
    parser.add_argument("--ap", default="1")
    parser.add_argument("--mode", default="Hotplug")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    script_dir = Path(__file__).resolve().parent
    connection = build_connection_arg(args.speed, args.ap, args.mode)

    obk_files = resolve_default_obk_files(script_dir)

    missing = [p for p in obk_files if not p.exists()]
    if missing:
        print("Missing OBK files:", file=sys.stderr)
        for p in missing:
            print(f"  - {p}", file=sys.stderr)
        return 2

    print("Checking connectivity...")
    run_cmd([CLI, "-c", connection])

    print("Checking product state...")
    is_open = detect_open_state(connection)

    if not is_open:
        print("Regress the device manually")

    for obk in obk_files:
        print(f"Provisioning OBK: {obk}")
        run_cmd([CLI, "-c", connection, "-sdp", str(obk)])

    print("OBK provisioning sequence completed.")


if __name__ == "__main__":
    raise main()
