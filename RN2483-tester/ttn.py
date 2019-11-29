class Ttn:
    def __init__(self, modem):
        self.modem = modem

    def join_abp(self, dev_address, nwk_session_key, app_session_key):
        frequency_band = 868
        hw_eui = self.modem.system.get_hweui().rstrip("\r\n")

        # Reset LoRaWAN settings, all previously set keys will be cleared.
        self.modem.lorawan.reset(frequency_band)

        # Set the needed credentials.
        self.modem.lorawan.set_device_eui(hw_eui)
        self.modem.lorawan.set_device_address(dev_address)
        self.modem.lorawan.set_network_session_key(nwk_session_key)
        self.modem.lorawan.set_app_session_key(app_session_key)

        # Set the TX output power to 14 dBm (25 mW).
        self.modem.lorawan.set_output_power(1)

        # Turn on Adaptive Data Rate (ADR)
        self.modem.lorawan.set_adaptive_data_rate("on")

        # Set the data rate.
        # SF12 = 0, SF11 = 1, SF10 = 2, SF9 = 3, SF8 = 4, SF7 = 5
        self.modem.lorawan.set_data_rate(5)

        # Save LoRaWAN settings to the EEPROM.
        #self.modem.lorawan.save()

        # Attempt to join the network.
        return self.modem.lorawan.join("abp")

    def transmit(self, data):
        return self.modem.lorawan.transmit("uncnf", 1, data)
