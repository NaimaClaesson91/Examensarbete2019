class SysCmd:
    '''RN2483 System commands.'''


    def __init__(self, modem):
        self.modem = modem


    def eeprom_read(self, address):
        '''Read a byte(HEX) from the modules EEPROM at given address(HEX)'''
        return self.modem.send_cmd(f"sys get nvm {address:02x}")


    def eeprom_save(self, address, byte):
        '''Save a byte(HEX) in the modules EEPROM at given address(HEX).'''
        return self.modem.send_cmd(f"sys set nvm {address:02x} {byte:02x}")


    def sleep(self, length):
        '''Puts the module to sleep for the specified amount of milliseconds.'''
        return self.modem.send_cmd(f"sys sleep {length}")


    def reset(self):
        '''Reset and restart module.'''
        return self.modem.send_cmd("sys reset")


    def factory_reset(self):
        '''Reset module configuration to factory default values.'''
        return self.modem.send_cmd("sys factoryRESET")


    def get_version(self):
        '''Get module firmware version and release date.'''
        return self.modem.send_cmd("sys get ver")


    def get_voltage(self):
        '''Get module VDD voltage.'''
        return self.modem.send_cmd("sys get vdd")


    def get_hweui(self):
        '''Get module Hardware EUI.'''
        return self.modem.send_cmd("sys get hweui")
