import serial
import sys
from serial import SerialException

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
        except SerialException:
            sys.exit("Failed to open serial port, exiting...")

        return self.ser.name

    def serial_close(self):
        '''Stop the serial communication.'''
        self.ser.close()

    def send_cmd(self, cmd):
        '''Send command to module and return the response.'''
        self.ser.write(bytes(cmd + "\r\n", "utf-8"))
        response = self.ser.readline().decode("utf-8")

        return response

    def get_version(self):
        '''Get firmware version and release date.'''
        return self.send_cmd("sys get ver")
