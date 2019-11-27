#!/usr/bin/env python3

'''Simple application for testing RN2483 modules from Microchip.'''

import sys
from rn2483 import Rn2483
from sys_cmd import SysCmd

def main():
    port = sys.argv[1]
    modem = Rn2483(port)
    sys_cmd = SysCmd(modem)

    print(f"Connected to {modem.open()}\n")
    print(sys_cmd.get_version())

    print("Module sleeping for 2000 ms...")
    print(sys_cmd.sleep(2000))

    # User-available EEPROM starts at address 768 and ends at 1023.
    #print(sys_cmd.eeprom_save(768, 2))
    #print(sys_cmd.eeprom_read(768))

    print(f"VDD (mV): {sys_cmd.get_voltage()}")
    print(f"Hardware EUI: {sys_cmd.get_hweui()}")

    modem.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Usage: main.py <port>")

    main()
