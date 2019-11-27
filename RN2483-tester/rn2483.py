import serial
import sys

class Lora:
    """Library for RN2483 modules from Microchip."""

    def __init__(self, port):
        self.ser = serial.Serial()
        self.ser.port = port
        self.ser.baudrate = 57600
        self.ser.bytesize = 8
        self.ser.parity = 'N'
        self.ser.stopbits = 1

    def serial_open(self):
        '''Start the serial communication.'''
        try:
            self.ser.open()
        except serial.SerialException:
            sys.exit(f"Failed to open port {self.ser.port}, exiting...")

        return self.ser.name

    def serial_close(self):
        '''Stop the serial communication.'''
        self.ser.close()

    def send_cmd(self, cmd):
        '''Send command to module and return the response.'''
        self.ser.write(bytes(f"{cmd}\r\n", "utf-8"))
        response = self.ser.readline().decode("utf-8")

        return response

    def eeprom_read(self, address):
        '''Read a byte(HEX) from the modules EEPROM at given address(HEX)'''
        return self.send_cmd(f"sys get nvm {address:02x}")

    def eeprom_save(self, address, byte):
        '''Save a byte(HEX) in the modules EEPROM at given address(HEX).'''
        return self.send_cmd(f"sys set nvm {address:02x} {byte:02x}")

    def sleep(self, length):
        '''Puts the module to sleep for the specified amount of milliseconds.'''
        return self.send_cmd(f"sys sleep {length}")

    def reset(self):
        '''Reset and restart module.'''
        return self.send_cmd("sys reset")

    def factory_reset(self):
        '''Reset module configuration to factory default values.'''
        return self.send_cmd("sys factoryRESET")

    def get_version(self):
        '''Get module firmware version and release date.'''
        return self.send_cmd("sys get ver")

    def get_voltage(self):
        '''Get module VDD voltage.'''
        return self.send_cmd("sys get vdd")

    def get_hweui(self):
        '''Get module Hardware EUI.'''
        return self.send_cmd("sys get hweui")
