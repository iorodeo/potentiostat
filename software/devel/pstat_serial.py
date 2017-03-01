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

    def get_param(self,test):
        cmd_dict = {'command': 'getParam', 'test': test} 
        rsp_dict = self.send_cmd(cmd_dict)
        return rsp_dict

    def set_param(self,test,param):
        cmd_dict = {'command': 'setParam', 'test': test, 'param': param}
        rsp_dict = self.send_cmd(cmd_dict)
        return rsp_dict

    def send_cmd(self,cmd_dict):
        cmd_json = json.dumps(cmd_dict)
        self.write(cmd_json + '\n')
        rsp_json = self.readline()
        rsp_json = rsp_json.strip()
        rsp_dict = json.loads(rsp_json)
        return rsp_dict




