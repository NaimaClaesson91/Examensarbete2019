#!/usr/bin/env python3

'''Simple application for testing RN2483 modules from Microchip.'''

import sys
import rn2483

def main():
    port = sys.argv[1]
    lora = rn2483.Lora(port)

    print(f"Connected to {lora.serial_open()}\n")
    print(lora.get_version())

    lora.serial_close()

if __name__ == "__main__":
    if len(sys.argv) == 2:
        main()
    else:
        sys.exit("Usage: main.py <port>")
