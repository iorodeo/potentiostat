from __future__ import print_function
import serial
import time
import json

# Json message keys
CommandKey = 'command'
ResponseKey = 'response'
MessageKey = 'message'
SuccessKey = 'success'
TestKey = 'test'
ParamKey = 'param'

# Commands
GetParamCmd = 'getParam'
SetParamCmd = 'setParam'

class Potentiostat(serial.Serial):
    
    ResetSleepDt = 0.0
    Baudrate = 115200
    Timeout = 2.0

    def __init__(self, port, timeout=10.0, debug=False):
        params = {'baudrate': self.Baudrate, 'timeout': self.Timeout}
        super(Potentiostat,self).__init__(port,**params)
        time.sleep(self.ResetSleepDt)

    def get_param(self,testname):
        cmd_dict = {CommandKey: GetParamCmd, TestKey: testname} 
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)
        return msg_dict[ResponseKey][ParamKey]

    def set_param(self,testname,param):
        cmd_dict = {CommandKey: SetParamCmd, TestKey: testname, ParamKey: param}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)
        return msg_dict[ResponseKey][ParamKey]

    def send_cmd(self,cmd_dict):
        cmd_json = json.dumps(cmd_dict)
        self.write(cmd_json + '\n')
        msg_json = self.readline()
        msg_json = msg_json.strip()
        msg_dict = json.loads(msg_json)
        return msg_dict

    def check_cmd_msg(self,cmd_dict,msg_dict):
        self.check_for_success(msg_dict)
        self.check_cmd_match(cmd_dict,msg_dict)
        if TestKey in cmd_dict:
            self.check_test_match(cmd_dict,msg_dict)

    def check_for_success(self,msg_dict):
        if not msg_dict[SuccessKey]: 
            raise IOError(msg_dict[MessageKey])

    def check_cmd_match(self,cmd_dict,msg_dict):
        cmd_sent = cmd_dict[CommandKey]
        cmd_recv = msg_dict[ResponseKey][CommandKey]
        if cmd_recv != cmd_sent: 
            raise IOError('command sent, {0}, not same as received, {1}'.format(cmd_sent, cmd_recv))

    def check_test_match(self,cmd_dict,msg_dict): 
        test_sent = cmd_dict[TestKey]
        test_recv = msg_dict[ResponseKey][TestKey]
        if test_recv != test_sent:
            raise IOError('testname sent, {0}, not same as received, {1}'.format(test_sent,test_recv))








