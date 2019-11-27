class LorawanCmd:
    '''RN2483 LoRaWAN protocol commands.'''

    def __init__(self, modem):
        self.modem = modem

    def reset(self, band):
        '''Reset the LoRaWAN stack and initialize it with default params.'''
        return self.modem.send_cmd(f"mac reset {band}") 

    def join(self, mode):
        '''Attempt to join the network using OTAA or ABP.'''
        return self.modem.send_cmd(f"mac join {mode}")
