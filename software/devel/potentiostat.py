from __future__ import print_function
import serial
import time
import json
import atexit
import contextlib
#import progressbar

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
VoltRangeKey = 'voltRange'
CurrRangeKey = 'currRange'
DeviceIdKey = 'deviceId'
SamplePeriodKey = 'samplePeriod'

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
GetSamplePeriodCmd = 'getSamplePeriod'
SetSamplePeriodCmd = 'setSamplePeriod'

# Voltage ranges
VoltRange1V = '1V'
VoltRange2V = '2V'
VoltRange5V = '5V'
VoltRange10V = '10V'
VoltRangeList = [VoltRange1V, VoltRange2V, VoltRange5V, VoltRange10V]

# Current Ranges
CurrRange60nA = '60nA'
CurrRange100nA = '100nA'
CurrRange1uA = '1uA'
CurrRange10uA = '10uA'
CurrRange100uA = '100uA'
CurrRange1000uA = '1000uA'

CurrRangeListNanoAmp = [CurrRange1uA, CurrRange10uA, CurrRange100nA, CurrRange60nA]
CurrRangeListNormal = [CurrRange1uA, CurrRange10uA, CurrRange100uA, CurrRange1000uA]
HwVariantToCurrRangeList = {
        'normal' :CurrRangeListNormal, 
        'nanoAmp': CurrRangeListNanoAmp
        }


class Potentiostat(serial.Serial):
    
    ResetSleepDt = 0.0
    Baudrate = 115200
    Timeout = 2.0

    def __init__(self, port, timeout=10.0, debug=False):
        params = {'baudrate': self.Baudrate, 'timeout': self.Timeout}
        super(Potentiostat,self).__init__(port,**params)
        time.sleep(self.ResetSleepDt)
        self.hw_variant = 'normal' 
        atexit.register(self.stop_test)
        while self.inWaiting() > 0:
            val = self.read()

    def set_hardware_variant(self,variant):
        if not variant in HwVariantToCurrRangeList:
            raise RuntimeError('unknown hardware variant, {0}'.format(variant))
        self.hw_variant = variant

    def get_hardware_variant(self):
        return self.hw_variant

    def run_test(self, testname, display='pbar', filename=None):
        cmd_dict = {CommandKey: RunTestCmd, TestKey: testname}
        msg_dict = self.send_cmd(cmd_dict)

        #if display == 'pbar':
        #    widgets = [progressbar.Percentage(),progressbar.Bar()]
        #    pbar = progressbar.ProgressBar(widgets=widgets )

        done = False
        tsec_list = [] 
        volt_list = [] 
        curr_list = []

        none_context = contextlib.contextmanager(lambda: iter([None]))()

        with (open(filename,'w') if filename is not None else none_context) as fid:

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
                    if display == 'data':
                        print('{0:1.3f}, {1:1.4f}, {2:1.4f}'.format(tsec,volt,curr))
                    #if display == 'pbar':
                    #    pass
                    if fid is not None:
                        fid.write('{0:1.3f}, {1:1.4f}, {2:1.4f}\n'.format(tsec,volt,curr))
                else:
                    done = True

        return tsec_list, volt_list, curr_list 

    def stop_test(self):
        cmd_dict = {CommandKey: StopTestCmd}
        msg_dict = self.send_cmd(cmd_dict)

    def get_volt(self):
        cmd_dict = {CommandKey: GetVoltCmd}
        msg_dict = self.send_cmd(cmd_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt

    def set_volt(self,volt):
        cmd_dict = {CommandKey: SetVoltCmd, VoltKey: volt}
        msg_dict = self.send_cmd(cmd_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt

    def get_curr(self):
        cmd_dict = {CommandKey: GetCurrCmd}
        msg_dict = self.send_cmd(cmd_dict)
        curr = msg_dict[ResponseKey][CurrKey]
        return curr

    def get_param(self,testname):
        cmd_dict = {CommandKey: GetParamCmd, TestKey: testname} 
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][ParamKey]

    def set_param(self,testname,param):
        cmd_dict = {CommandKey: SetParamCmd, TestKey: testname, ParamKey: param}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][ParamKey]

    def set_volt_range(self,volt_range):
        if not volt_range in VoltRangeList:
            raise ValueError('unknown voltage range')
        cmd_dict = {CommandKey: SetVoltRangeCmd, VoltRangeKey: volt_range}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VoltRangeKey]

    def get_volt_range(self):
        cmd_dict = {CommandKey: GetVoltRangeCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VoltRangeKey]

    def set_curr_range(self,curr_range):
        if not curr_range in HwVariantToCurrRangeList[self.hw_variant]:
            raise ValueError('unknown current range')
        cmd_dict = {CommandKey: SetCurrRangeCmd, CurrRangeKey: curr_range}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][CurrRangeKey]

    def get_curr_range(self):
        cmd_dict = {CommandKey: GetCurrRangeCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][CurrRangeKey]

    def set_device_id(self,device_id):
        cmd_dict = {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][DeviceIdKey]

    def get_device_id(self):
        cmd_dict = {CommandKey: GetDeviceIdCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][DeviceIdKey]

    def set_sample_period(self,sample_period):
        pass

    def get_sample_period(self):
        pass

    def set_sample_rate(self,sample_rate):
        pass

    def get_sample_rate(self):
        pass

    def send_cmd(self,cmd_dict):
        cmd_json = json.dumps(cmd_dict)
        self.write(cmd_json + '\n')
        msg_json = self.readline()
        msg_json = msg_json.strip()
        msg_dict = json.loads(msg_json)
        self.check_cmd_msg(cmd_dict,msg_dict)
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






