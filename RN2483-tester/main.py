#!/usr/bin/env python3

'''Simple application for testing RN2483 modules from Microchip.'''

import sys
from rn2483 import Rn2483

def main():
    port = sys.argv[1]
    modem = Rn2483(port)

    print(f"Connected to {modem.open()}\n")
    print(modem.system.get_version())

    print("Module sleeping for 2000 ms...")
    print(modem.system.sleep(2000))

    # User-available EEPROM starts at address 768 and ends at 1023.
    #print(modem.system.eeprom_save(768, 2))
    #print(modem.system.eeprom_read(768))

    print(f"VDD (mV): {modem.system.get_voltage()}")
    print(f"Hardware EUI: {modem.system.get_hweui()}")

    print(f"Frequency (Hz): {modem.radio.get_freq()}")
    print(f"Transmit output power (dBm): {modem.radio.get_pwr()}")

    # The mac pause command must be called before any radio transmission
    # or reception, even if no MAC operations have been initiated before.

    print(f"Module status: {modem.lorawan.get_status()}")

    modem.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Usage: main.py <port>")

    main()
