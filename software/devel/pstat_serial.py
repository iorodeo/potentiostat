from __future__ import print_function
import serial
import time
import json


class PStatSerial(serial.Serial):

    ResetSleepDt = 0.0

    def __init__(self, port, timeout=10.0, debug=False):
        params = {'baudrate': 115200, 'timeout': 2.0}
        super(PStatSerial,self).__init__(port,**params)
        time.sleep(self.ResetSleepDt)

    def send_cmd(self,cmd_dict):
        cmd_json = json.dumps(cmd_dict)
        print('cmd_json = ', cmd_json)
        self.write(cmd_json + '\n')
        rsp = self.readline()
        rsp = rsp.strip()
        rsp_dict = json.loads(rsp)
        return rsp_dict

