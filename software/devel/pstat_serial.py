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
        msg_dict = self.send_cmd(cmd_dict)

        if not msg_dict['success']: 
            raise IOError(msg_dict['message'])

        response = msg_dict['response']

        if response['command'] != 'getParam': 
            raise IOError('command sent, {0}, not same as received, {1}'.format(command, response['command']))

        if response['test'] != test:
            raise IOError('test sent, {0}, not same as received, {1}'.format(test,response['test']))

        return response['param']


    def set_param(self,test,param):
        cmd_dict = {'command': 'setParam', 'test': test, 'param': param}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict

    def send_cmd(self,cmd_dict):
        cmd_json = json.dumps(cmd_dict)
        self.write(cmd_json + '\n')
        msg_json = self.readline()
        msg_json = msg_json.strip()
        msg_dict = json.loads(msg_json)
        return msg_dict




