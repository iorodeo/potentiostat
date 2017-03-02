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
TimeKey = 't'
VoltKey = 'v'
CurrKey = 'i'

# Commands
RunTestCmd  = 'runTest'
StopTestCmd = 'stopTest'
GetVoltCmd = 'getVolt'
SetVoltCmd = 'setVolt'
GetCurrCmd = 'getCurr'
GetParamCmd = 'getParam'
SetParamCmd = 'setParam'
GetVoltRangeCmd = 'getVoltRange'
SetVoltRangeCmd = 'setVoltRange'
GetCurrRangeCmd = 'getCurrRange'
SetCurrRangeCmd = 'setCurrRange'
GetDeviceIdCmd = 'getDeviceId'
SetDeviceIdCmd = 'setDeviceId'


class Potentiostat(serial.Serial):
    
    ResetSleepDt = 0.0
    Baudrate = 115200
    Timeout = 2.0

    def __init__(self, port, timeout=10.0, debug=False):
        params = {'baudrate': self.Baudrate, 'timeout': self.Timeout}
        super(Potentiostat,self).__init__(port,**params)
        time.sleep(self.ResetSleepDt)

    def run_test(self, testname):
        cmd_dict = {CommandKey: RunTestCmd, TestKey: testname}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)

        done = False
        tsec_list = [] 
        volt_list = [] 
        curr_list = []

        while not done:
            sample_json = self.readline()
            sample_json = sample_json.strip()
            sample_dict = json.loads(sample_json)
            if len(sample_dict) > 0:
                tsec = millisecondToSecond(sample_dict[TimeKey])
                volt = sample_dict[VoltKey]
                curr = sample_dict[CurrKey]
                tsec_list.append(tsec)
                volt_list.append(volt)
                curr_list.append(curr)
                print('{0:1.3f}, {1:1.4f}, {2:1.4f}'.format(tsec,volt,curr))
            else:
                done = True
        return tsec_list, volt_list, curr_list 

    def stop_test(self):
        cmd_dict = {CommandKey: StopTestCmd}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)

    def get_volt(self):
        cmd_dict = {CommandKey: GetVoltCmd}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt

    def set_volt(self,volt):
        cmd_dict = {CommandKey: SetVoltCmd, VoltKey: volt}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt

    def get_curr(self):
        cmd_dict = {CommandKey: GetCurrCmd}
        msg_dict = self.send_cmd(cmd_dict)
        self.check_cmd_msg(cmd_dict,msg_dict)
        curr = msg_dict[ResponseKey][CurrKey]
        return curr

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

    def set_volt_range(self,volt_range):
        pass

    def get_volt_range(self):
        pass

    def set_curr_range(self,curr_range):
        pass

    def get_curr_range(self):
        pass

    def set_device_id(self,device_id):
        pass

    def get_device_id(self):
        pass

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


# Utility functions
# ---------------------------------------------------------------------------------------

def millisecondToSecond(value):
    return 1.0e-3*value

def secondToMillisecond(value):
    return int(1.0e3*value)






