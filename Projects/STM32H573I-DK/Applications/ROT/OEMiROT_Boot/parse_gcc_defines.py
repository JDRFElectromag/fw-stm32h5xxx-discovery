#!/usr/bin/env python3
import re
import sys

def extract_gcc_defines(filepath: str) -> list[tuple[str, str | None]]:
    with open(filepath) as f:
        content = f.read()

    # Require -D to be preceded by whitespace or a quote to avoid matching
    # -D embedded inside path strings (e.g. "-MT...mbed-crypto/...d")
    pattern = r"(?:(?<=\s)|(?<=')|(?<=\"))-D([A-Za-z_][A-Za-z0-9_]*(?:=[^\s'\"]*)?)"
    matches = re.findall(pattern, content)

    seen = set()
    unique: list[tuple[str, str | None]] = []
    for m in matches:
        if m not in seen:
            seen.add(m)
            if "=" in m:
                name, value = m.split("=", 1)
            else:
                name, value = m, None
            unique.append((name, value))
    return unique

if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else "bootloader-build-output.md"
    defines = extract_gcc_defines(path)
    for name, value in defines:
        if value is not None:
            print(f"-D{name}={value}  (name={name}, value={value})")
        else:
            print(f"-D{name}")
