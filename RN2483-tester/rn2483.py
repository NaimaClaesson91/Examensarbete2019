import serial
import sys
from sys_cmd import SysCmd
from lorawan_cmd import LorawanCmd
from radio_cmd import RadioCmd

class Rn2483:
    """Library for RN2483 modules from Microchip."""

    def __init__(self, port):
        self.ser = serial.Serial()
        self.ser.port = port
        self.ser.baudrate = 57600
        self.ser.bytesize = 8
        self.ser.parity = 'N'
        self.ser.stopbits = 1
        
        self.system = SysCmd(self)
        self.lorawan = LorawanCmd(self)
        self.radio = RadioCmd(self)

    def open(self):
        '''Open the serial communication.'''
        try:
            self.ser.open()
        except serial.SerialException:
            sys.exit(f"Failed to open port {self.ser.port}, exiting...")

        return self.ser.name

    def close(self):
        '''Close the serial communication.'''
        self.ser.close()

    def send_cmd(self, cmd):
        '''Send command to module and return the response.'''
        self.ser.write(bytes(f"{cmd}\r\n", "utf-8"))
        response = self.ser.readline().decode("utf-8")

        return response
