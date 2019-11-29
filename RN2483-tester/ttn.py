class Ttn:
    '''Module for connecting to The Things Network.'''

    def __init__(self, modem):
        self.modem = modem

    def configure_frequency_plan(self):
        '''Configure the EU863-870 frequency plan.'''

        # Calculate the duty cycle value.
        duty_cycle_pct = 1
        channels = 8
        duty_cycle_pct_per_channel = duty_cycle_pct / channels
        duty_cycle = int((100 / duty_cycle_pct_per_channel) - 1)

        frequencies = [868100000, 868300000, 868500000, 867100000,
                       867300000, 867500000, 867700000, 867900000]

        for channel in range(channels):
            self.modem.lorawan.set_ch_duty_cycle(channel, duty_cycle)
            self.modem.lorawan.set_ch_frequency(channel, frequencies[channel])

            if frequencies[channel] == 868300000:
                # SF7BW125 to SF12BW125 and SF7BW250
                self.modem.lorawan.set_ch_data_rate_range(channel, 0, 6)
            else:
                # SF7BW125 to SF12BW125
                self.modem.lorawan.set_ch_data_rate_range(channel, 0, 5)

            # Activate channel.
            self.modem.lorawan.set_ch_status(channel, "on")

        # Set the TX output power to 14 dBm.
        self.modem.lorawan.set_output_power(1)

    def join_abp(self, dev_address, nwk_session_key, app_session_key):
        '''Join a LoRaWAN network using Activation By Personalisation.'''
        frequency_band = 868

        # Reset LoRaWAN settings, all previously set keys will be cleared.
        self.modem.lorawan.reset(frequency_band)

        # Set the needed credentials.
        self.modem.lorawan.set_device_address(dev_address)
        self.modem.lorawan.set_network_session_key(nwk_session_key)
        self.modem.lorawan.set_app_session_key(app_session_key)

        # Turn on Adaptive Data Rate (ADR)
        self.modem.lorawan.set_adaptive_data_rate("on")

        # Set the initial data rate.
        # SF12BW125 = 0, SF11BW125 = 1, SF10BW125 = 2, SF9BW125 = 3,
        # SF8BW125 = 4, SF7BW125 = 5, SF7BW250 = 6
        self.modem.lorawan.set_data_rate(5)

        # Configure the second receive window for SF9BW125.
        self.modem.lorawan.set_second_rx_window(3, 869525000)

        # Save LoRaWAN settings to the EEPROM.
        #self.modem.lorawan.save()

        # Attempt to join the network.
        return self.modem.lorawan.join("abp")

    def transmit_unconfirmed_packet(self, data):
        return self.modem.lorawan.transmit("uncnf", 1, data)

    def transmit_confirmed_packet(self, data):
        return self.modem.lorawan.transmit("cnf", 1, data)
