#!/usr/bin/env python3

'''Simple application for testing RN2483 modules from Microchip.'''

import sys
import rn2483

def main():
    port = sys.argv[1]
    lora = rn2483.Lora(port)

    print(f"Connected to {lora.serial_open()}\n")
    print(lora.get_version())

    print("Module sleeping for 2000 ms...")
    print(lora.sleep(2000))

    # User-available EEPROM starts at address 768 and ends at 1023.
    #print(lora.eeprom_save(768, 2))
    #print(lora.eeprom_read(768))

    print(f"VDD (mV): {lora.get_voltage()}")
    print(f"Hardware EUI: {lora.get_hweui()}")

    lora.serial_close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Usage: main.py <port>")

    main()
