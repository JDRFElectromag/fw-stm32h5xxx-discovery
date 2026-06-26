#!/usr/bin/env python3
"""Extract GCC include paths from build logs using regex."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path


INCLUDE_REGEX = re.compile(
    r"""
    (?:^|\s)
    (?:
      -I(?:\s+)?
      | -isystem\s+
      | -iquote\s+
      | -idirafter\s+
    )
    (?:
      "([^"]+)"
      | '([^']+)'
      | ([^\s"']+)
    )
    """,
    re.VERBOSE,
)


def extract_include_paths(text: str) -> list[str]:
    """Return include paths in encounter order (duplicates kept)."""
    paths: list[str] = []
    for match in INCLUDE_REGEX.finditer(text):
        path = next(group for group in match.groups() if group is not None)
        paths.append(path)
    return paths


def unique_keep_order(items: list[str]) -> list[str]:
    seen: set[str] = set()
    out: list[str] = []
    for item in items:
        if item not in seen:
            seen.add(item)
            out.append(item)
    return out


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Parse GCC include paths from a build log."
    )
    parser.add_argument("input", type=Path, help="Path to the build log file")
    parser.add_argument(
        "--all",
        action="store_true",
        help="Print all matches, including duplicates",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    if not args.input.exists():
        print(f"error: file not found: {args.input}", file=sys.stderr)
        return 1

    text = args.input.read_text(encoding="utf-8", errors="replace")
    paths = extract_include_paths(text)

    if not args.all:
        paths = unique_keep_order(paths)

    for path in paths:
        print(path)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
