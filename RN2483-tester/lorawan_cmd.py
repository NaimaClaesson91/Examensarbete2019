class LorawanCmd:
    '''RN2483 LoRaWAN protocol commands.'''

    def __init__(self, modem):
        self.modem = modem

    def reset(self, band):
        '''Reset the LoRaWAN stack and initialize it with default params.'''
        return self.modem.send_cmd(f"mac reset {band}")

    def transmit(self, payload_type, port, data):
        '''Sends the data on specified port with default LoRaWAN parameters.'''
        return self.modem.send_cmd(f"mac tx {payload_type} {port} {data}")

    def join(self, mode):
        '''Attempt to join the network using OTAA or ABP.'''
        return self.modem.send_cmd(f"mac join {mode}")

    def save(self):
        '''Saves LoRaWAN Class A configuration parameters to the user EEPROM.'''
        return self.modem.send_cmd("mac save")

    def force_enable(self):
        '''Enables the RN2483 module after the LoRaWAN network server commanded
           the end device to become silent immediately.'''
        return self.modem.send_cmd("mac forceEnable")

    def pause(self):
        '''Pauses LoRaWAN stack functionality to allow radio configuration.'''
        return self.modem.send_cmd("mac pause")

    def resume(self):
        '''Restores the LoRaWAN stack functionality.'''
        return self.modem.send_cmd("mac resume")

    def set_app_key(self, app_key):
        '''Sets the application key for the RN2483 module.'''
        return self.modem.send_cmd(f"mac set appkey {app_key}")

    def set_app_session_key(self, app_session_key):
        '''Sets the application session key for the RN2483 module.'''
        return self.modem.send_cmd(f"mac set appskey {app_session_key}")

    def set_automatic_reply(self, state):
        '''Sets the state of the automatic reply.'''
        return self.modem.send_cmd(f"mac set ar {state}")

    def set_battery_level(self, battery_level):
        '''Sets the battery level needed for Device Status Answer frame.'''
        return self.modem.send_cmd(f"mac set bat {battery_level}")

    def set_ch_frequency(self, channel, frequency):
        '''Sets the operational frequency on the given channel ID.'''
        return self.modem.send_cmd(f"mac set ch freq {channel} {frequency}")

    def set_ch_duty_cycle(self, channel, duty_cycle):
        '''Sets the duty cycle on the given channel ID.'''
        return self.modem.send_cmd(f"mac set ch dcycle {channel} {duty_cycle}")

    def set_ch_data_rate_range(self, channel, min_range, max_range):
        '''Sets the operating data range, min to max, for the given channel ID.'''
        return self.modem.send_cmd(f"mac set ch drrange {channel} {min_range} {max_range}")

    def set_ch_status(self, channel, status):
        '''Sets the operation of the given channel ID.'''
        return self.modem.send_cmd(f"mac set ch status {channel} {status}")

    def set_class(self, lorawan_class):
        '''Sets the LoRaWAN operating class.'''
        return self.modem.send_cmd(f"mac set class {lorawan_class}")

    def set_device_address(self, address):
        '''Sets the unique network address for the RN2483 module.'''
        return self.modem.send_cmd(f"mac set devaddr {address}")

    def set_device_eui(self, device_eui):
        '''Sets the globally unique identifier for the RN2483 module.'''
        return self.modem.send_cmd(f"mac set deveui {device_eui}")

    def set_downlink_frame_counter(self, value):
        '''Sets the value of the downlink frame counter that will be used for
           the next downlink reception.'''
        return self.modem.send_cmd(f"mac set dnctr {value}")

    def set_data_rate(self, data_rate):
        '''Sets the data rate to be used for the next transmissions.'''
        return self.modem.send_cmd(f"mac set dr {data_rate}")

    def set_link_check_interval(self, interval):
        '''Sets the time interval for the link check process to be triggered.'''
        return self.modem.send_cmd(f"mac set linkchk {interval}")

    def set_multicast(self, state):
        '''Sets the multicast state to on, or off.'''
        return self.modem.send_cmd(f"mac set mcast {state}")

    def set_multicast_app_session_key(self, key):
        '''Sets the multicast application session key.'''
        return self.modem.send_cmd(f"mac set mcastappskey {key}")

    def set_multicast_device_address(self, address):
        '''Sets the multicast network device address.'''
        return self.modem.send_cmd(f"mac set mcastdevaddr {address}")

    def set_multicast_downlink_frame_counter(self, value):
        '''Sets the value of the multicast downlink frame counter that will be
           used for the next downlink reception.'''
        return self.modem.send_cmd(f"mac set mcastdnctr {value}")

    def set_multicast_network_session_key(self, key):
        '''Sets the multicast network session key.'''
        return self.modem.send_cmd(f"set mcastnwkskey {key}")

    def set_network_session_key(self, key):
        '''Sets the network session key for the RN2483 module.'''
        return self.modem.send_cmd(f"set nwkskey {key}")

    def set_output_power(self, power):
        '''Sets the output power to be used on the next transmissions.'''
        return self.modem.send_cmd(f"set pwridx {power}")

    def set_retransmissions(self, value):
        '''Sets the number of retransmissions to be used for an uplink confirmed
           package.'''
        return self.modem.send_cmd(f"set retx {value}")

    def set_second_rx_window(self, data_rate, frequency):
        '''Sets the data rate and frequency used for the second Receive window.'''
        return self.modem.send_cmd(f"set rx2 {data_rate} {frequency}")

    def set_first_rx_delay(self, delay):
        '''Sets the value used for the first Receive window delay.'''
        return self.modem.send_cmd(f"set rxdelay1 {delay}")

    def set_sync_word(self, word):
        '''Sets the synchronization word for the LoRaWAN communication.'''
        return self.modem.send_cmd(f"set sync {word}")

    def set_uplink_frame_counter(self, value):
        '''Sets the value of the uplink frame counter that will be used for the
           next uplink transmission.'''
        return self.modem.send_cmd(f"set upctr {value}")

    def get_adaptive_data_rate(self):
        '''Gets the state of adaptive data rate for the device.'''
        return self.modem.send_cmd("mac get adr")

    def get_app_eui(self):
        '''Gets the application identifier for the end device.'''
        return self.modem.send_cmd("mac get appeui")

    def get_automatic_reply(self):
        '''Gets the state of the automatic reply.'''
        return self.modem.send_cmd("mac get ar")

    def get_ch_frequency(self, channel):
        '''Gets the module operation frequency for the specified channel ID.'''
        return self.modem.send_cmd(f"mac get ch freq {channel}")

    def get_ch_duty_cycle(self, channel):
        '''Gets the module duty cycle used for transmission on the specified
           channel ID.'''
        return self.modem.send_cmd(f"mac get ch dcycle {channel}")

    def get_ch_data_rate_range(self, channel):
        '''Gets the valid data rate range (min. to max.) allowed for the module
           on the specified channel ID.'''
        return self.modem.send_cmd(f"mac get ch drrange {channel}")

    def get_ch_status(self, channel):
        '''Gets the status for the specified channel ID to indicate if it is
           enabled for use.'''
        return self.modem.send_cmd(f"mac get ch status {channel}")

    def get_class(self):
        '''Gets the LoRaWAN operating class for the end device.'''
        return self.modem.send_cmd("mac get class")

    def get_duty_cycle_prescaler(self):
        '''Gets the duty cycle prescaler which can only be configured by the
           server.'''
        return self.modem.send_cmd("mac get dcycleps")

    def get_device_address(self):
        '''Gets the current stored unique network device address for that
           specific end device.'''
        return self.modem.send_cmd("mac get devaddr")

    def get_device_eui(self):
        '''Gets the current stored globally unique identifier for that specific
           end device.'''
        return self.modem.send_cmd("mac get deveui")

    def get_downlink_frame_counter(self):
        '''Gets the value of the downlink frame counter that will be used for
           the next downlink reception.'''
        return self.modem.send_cmd("mac get dnctr")

    def get_data_rate(self):
        '''Gets the data rate to be used for the next transmission.'''
        return self.modem.send_cmd("mac get dr")

    def get_gw_link_check(self):
        '''Gets the number of gateways that successfully received the last Link
           Check Request frame.'''
        return self.modem.send_cmd("mac get gwnb")

    def get_multicast(self):
        '''Gets the state of multicast reception for the end device.'''
        return self.modem.send_cmd("mac get mcast")

    def get_multicast_device_address(self):
        '''Gets the current stored multicast network device address for the end
           device.'''
        return self.modem.send_cmd("mac get mcastdevaddr")

    def get_multicast_downlink_frame_counter(self):
        '''Gets the value of the multicast downlink frame counter that will be
           used for the next multicast downlink reception.'''
        return self.modem.send_cmd("mac get mcastdnctr")

    def get_demodulation_margin(self):
        '''Gets the demodulation margin as received in the last Link Check
           Answer frame.'''
        return self.modem.send_cmd("mac get mrgn")

    def get_output_power(self):
        '''Gets the output power index value.'''
        return self.modem.send_cmd("mac get pwridx")

    def get_uplink_retransmission_count(self):
        '''Gets the number of retransmissions to be used for an uplink confirmed
           packet.'''
        return self.modem.send_cmd("mac get retx")

    def get_second_rx_window(self):
        '''Gets the data rate and frequency used for the second Receive window.'''
        return self.modem.send_cmd("mac get rx2")

    def get_rxdelay1(self):
        '''Gets the interval value stored for rxdelay1.'''
        return self.modem.send_cmd("mac get rxdelay1")

    def get_rxdelay2(self):
        '''Gets the interval value stored for rxdelay2.'''
        return self.modem.send_cmd("mac get rxdelay2")

    def get_status(self):
        '''Gets the current status of the RN2483 module.'''
        return self.modem.send_cmd("mac get status")

    def get_sync_word(self):
        '''Gets the synchronization word for the LoRaWAN communication.'''
        return self.modem.send_cmd("mac get sync")

    def get_uplink_frame_counter(self):
        '''Gets the value of the uplink frame counter that will be used for the
           next uplink transmission.'''
        return self.modem.send_cmd("mac get upctr")
