class RadioCmd:
    '''RN2483 Radio commands.'''

    def __init__(self, modem):
        self.modem = modem

    def set_afcbw(self, auto_freq_band):
        '''Set the value used by the automatic frequency correction bandwith.'''
        return self.modem.send_cmd(f"radio set afcbw {auto_freq_band}")

    def set_bitrate(self, bitrate):
        '''Set the frequency shift keying (FSK) bit rate.'''
        return self.modem.send_cmd(f"radio set bitrate {bitrate}")

    def set_bt(self, data_shape):
        '''Set the data shaping for FSK modulation type.'''
        return self.modem.send_cmd(f"radio set bt {data_shape}")

    def set_bw(self, bandwidth):
        '''Set the value used for the radio bandwith.'''
        return self.modem.send_cmd(f"radio set bw {bandwidth}")

    def set_cr(self, coding_rate):
        '''Set the coding rate used by the radio.'''
        return self.modem.send_cmd(f"radio set cr {coding_rate}")

    def set_crc(self, state):
        '''Set if a CRC header is to be used.'''
        return self.modem.send_cmd(f"radio set crc {state}")

    def set_fdev(self, frequency):
        '''Set the frequency deviation allowed by the end device.'''
        return self.modem.send_cmd(f"radio set fdev {frequency}")

    def set_freq(self, frequency):
        '''Set the current operation frequency for the radio.'''
        return self.modem.send_cmd(f"radio set freq {frequency}")

    def set_iqi(self, state):
        '''Set if IQ inversion is used.'''
        return self.modem.send_cmd(f"radio set iqi {state}")

    def set_mod(self, modulation):
        '''Set the module Modulation mode.'''
        return self.modem.send_cmd(f"radio set mod {modulation}")

    def set_prlen(self, length):
        '''Set the preamble length used during transmissions.'''
        return self.modem.send_cmd(f"radio set prlen {length}")

    def set_pwr(self, power):
        '''Set the output power level used by the radio during transmission.'''
        return self.modem.send_cmd(f"radio set pwr {power}")

    def set_rxbw(self, bandwidth):
        '''Set the operational receive bandwidth.'''
        return self.modem.send_cmd(f"radio set rxbw {bandwidth}")

    def set_sf(self, spreading_factor):
        '''Set the requested SF to be used during transmission.'''
        return self.modem.send_cmd(f"radio set sf {spreading_factor}")

    def set_sync(self, sync_word):
        '''Set the sync word used.'''
        return self.modem.send_cmd(f"radio set sync {sync_word}")

    def set_wdt(self, timeout_limit):
        '''Set the time-out limit for the radio Watchdog Timer.'''
        return self.modem.send_cmd(f"radio set wdt {timeout_limit}")

    def get_afcbw(self):
        '''Get the value used by the automatic frequency correction bandwidth.'''
        return self.modem.send_cmd("radio get afcbw")

    def get_bitrate(self):
        '''Get the frequency shift keying (FSK) bit rate.'''
        return self.modem.send_cmd("radio get bitrate")

    def get_bt(self):
        '''Get the data shaping for FSK modulation type.'''
        return self.modem.send_cmd("radio get bt")

    def get_bw(self):
        '''Get the value used for the radio bandwidth.'''
        return self.modem.send_cmd("radio get bw")

    def get_cr(self):
        '''Get the coding rate used by the radio.'''
        return self.modem.send_cmd("radio get cr")

    def get_crc(self):
        '''Get if a CRC header is to be used.'''
        return self.modem.send_cmd("radio get crc")

    def get_fdev(self):
        '''Get the frequency deviation allowed by the end device.'''
        return self.modem.send_cmd("radio get fdev")

    def get_freq(self):
        '''Get the current operation frequency for the radio.'''
        return self.modem.send_cmd("radio get freq")

    def get_iqi(self):
        '''Get if IQ inversion is used.'''
        return self.modem.send_cmd("radio get iqi")

    def get_mod(self):
        '''Get the module Modulation mode.'''
        return self.modem.send_cmd("radio get mod")

    def get_prlen(self):
        '''Get the preamble length used during transmissions.'''
        return self.modem.send_cmd("radio get prlen")

    def get_pwr(self):
        '''Get the output power level used by the radio during transmission.'''
        return self.modem.send_cmd("radio get pwr")

    def get_rssi(self):
        '''Get the RSSI value from the last received frame.'''
        return self.modem.send_cmd("radio get rssi")

    def get_rxbw(self):
        '''Get the operational receive bandwidth.'''
        return self.modem.send_cmd("radio get rxbw")

    def get_sf(self):
        '''Get the requested spreading factor to be used during transmission.'''
        return self.modem.send_cmd("radio get sf")

    def get_snr(self):
        '''Get the signal-to-noise ratio (SNR) of the last received packet.'''
        return self.modem.send_cmd("radio get snr")

    def get_sync(self):
        '''Get the syncronization word used for communication.'''
        return self.modem.send_cmd("radio get sync")

    def get_wdt(self):
        '''Get the time-out limit for the Watchdog Timer.'''
        return self.modem.send_cmd("radio get wdt")
