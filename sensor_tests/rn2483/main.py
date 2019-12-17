#!/usr/bin/env python3

'''Application for testing RN2483 modules from Microchip.'''

import sys
import time
from rn2483 import Rn2483
from ttn import Ttn


def main():
    port = sys.argv[1]
    modem = Rn2483(port)
    ttn = Ttn(modem)

    credentials = open("credentials.txt", "r")
    dev_address = credentials.readline().rstrip("\r\n")
    nwk_session_key = credentials.readline().rstrip("\r\n")
    app_session_key = credentials.readline().rstrip("\r\n")
    app_eui = credentials.readline().rstrip("\r\n")
    app_key = credentials.readline().rstrip("\r\n")
    credentials.close()

    print(f"Connected to {modem.open()}\n")
    print(modem.system.get_version())

    # Load the globally unique EUI that is stored in the hardware.
    dev_eui = modem.system.get_hweui().rstrip("\r\n")

    ttn.configure_frequency_plan()

    #print("Attempting join by ABP... ", end="")
    #print(ttn.join_abp(dev_address, nwk_session_key, app_session_key))

    print("Attempting join by OTAA...", end="")
    print(ttn.join_otaa(dev_eui, app_eui, app_key))

    time.sleep(15)
    print("Transmitting... ", end="")
    print(ttn.transmit_unconfirmed_packet("CD1E09B900F401099E7FFF"))

    #print("Module sleeping for 2000 ms...")
    #print(modem.system.sleep(2000))

    # User-available EEPROM starts at address 768 and ends at 1023.
    #print(modem.system.eeprom_save(768, 2))
    #print(modem.system.eeprom_read(768))


    #print(f"Frequency (Hz): {modem.radio.get_freq()}")
    #print(f"Transmit output power (dBm): {modem.radio.get_pwr()}")

    # The mac pause command must be called before any radio transmission
    # or reception, even if no MAC operations have been initiated before.

    modem.close()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Usage: main.py <port>")

    main()