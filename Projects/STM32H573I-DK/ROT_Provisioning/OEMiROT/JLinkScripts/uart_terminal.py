#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
import select
import sys
import termios
import tty


BAUD_RATE = 115200


def configure_tty(fd: int) -> None:
    attrs = termios.tcgetattr(fd)

    attrs[0] = 0
    attrs[1] = 0
    attrs[2] = termios.CREAD | termios.CLOCAL | termios.CS8
    attrs[3] = 0

    attrs[2] &= ~termios.PARENB
    attrs[2] &= ~termios.CSTOPB
    attrs[2] &= ~termios.CSIZE
    attrs[2] |= termios.CS8

    if hasattr(termios, "CRTSCTS"):
        attrs[2] &= ~termios.CRTSCTS

    attrs[4] = termios.B115200
    attrs[5] = termios.B115200
    attrs[6][termios.VMIN] = 1
    attrs[6][termios.VTIME] = 0

    termios.tcflush(fd, termios.TCIFLUSH)
    termios.tcsetattr(fd, termios.TCSANOW, attrs)


def chunk_size(value: str) -> int:
    size = int(value)
    if size < 2:
        raise argparse.ArgumentTypeError("chunk size must be at least 2 bytes")
    return size


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Read from and write to a Linux UART TTY device.",
    )
    parser.add_argument(
        "port",
        help="TTY device path, for example /dev/ttyACM0 or /dev/ttyUSB0.",
    )
    parser.add_argument(
        "--chunk-size",
        type=chunk_size,
        default=1024,
        help="Number of bytes to read per iteration from UART.",
    )
    return parser.parse_args()

def run_term(port, chunk_size=1024):
    fd = None
    stdin_fd = None
    stdin_settings = None
    try:
        fd = os.open(port, os.O_RDWR | os.O_NOCTTY)
        configure_tty(fd)
        if sys.stdin.isatty():
            stdin_fd = sys.stdin.fileno()
            stdin_settings = termios.tcgetattr(stdin_fd)
            tty.setcbreak(stdin_fd)

        print(
            f"Connected to {port} at {BAUD_RATE} 8N1.",
            file=sys.stderr,
        )
        print(
            "Type to send bytes to UART. Press Ctrl+C to stop.",
            file=sys.stderr,
        )
        while True:
            read_fds = [fd]
            if stdin_fd is not None:
                read_fds.append(stdin_fd)

            readable, _, _ = select.select(read_fds, [], [])

            if fd in readable:
                incoming = os.read(fd, chunk_size)
                if incoming:
                    sys.stdout.buffer.write(incoming)
                    sys.stdout.buffer.flush()

            if stdin_fd is not None and stdin_fd in readable:
                outgoing = os.read(stdin_fd, 1)
                if not outgoing:
                    continue
                os.write(fd, outgoing)
    except OSError as exc:
        print(f"Serial error: {exc}", file=sys.stderr)
        return 1
    except KeyboardInterrupt:
        print("\nStopped.", file=sys.stderr)
        return 0
    finally:
        if stdin_fd is not None and stdin_settings is not None:
            termios.tcsetattr(stdin_fd, termios.TCSANOW, stdin_settings)
        if fd is not None:
            os.close(fd)

def main() -> int:
    args = parse_args()
    run_term(args.port, args.chunk_size)

if __name__ == "__main__":
    raise SystemExit(main())
