"""
============
potentiostat
============

    This module implements the serial interface to the Rodeostat open source 
    Potentiostat Shield.

    :copyright: (c) 2017 by IO Rodeo 
    :license: MIT, see LICENSE.txt for more details.
"""
from __future__ import print_function
import serial
import time
import json
import atexit
import contextlib
import progressbar


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
RefVoltKey = 'r'
VoltRangeKey = 'voltRange'
CurrRangeKey = 'currRange'
DeviceIdKey = 'deviceId'
SamplePeriodKey = 'samplePeriod'
TestDoneTimeKey = 'testDoneTime'
StepArrayKey = 'step'
TestNameArrayKey = 'testNames'
VersionKey = 'version'
VariantKey = 'variant'

# Commands
RunTestCmd  = 'runTest'
StopTestCmd = 'stopTest'
GetVoltCmd = 'getVolt'
SetVoltCmd = 'setVolt'
GetCurrCmd = 'getCurr'
GetRefVoltCmd = 'getRefVolt'
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
GetTestDoneTimeCmd = 'getTestDoneTime'
GetTestNamesCmd = 'getTestNames'
GetVersionCmd = 'getVersion'
GetVariantCmd = 'getVariant'

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
CurrRangeListMicroAmp = [CurrRange1uA, CurrRange10uA, CurrRange100uA, CurrRange1000uA]
HwVariantToCurrRangeList = {
        'microAmpV0.1' :  CurrRangeListMicroAmp, 
        'nanoAmpV0.1'  :  CurrRangeListNanoAmp
        }

TimeUnitToScale = {'s': 1.e-3, 'ms': 1}

class Potentiostat(serial.Serial):

    """Provides a high level interface  performing serial communications with the Rodeostat. 

    :param str port: serial port associated with the Rodeostat, e.g. /dev/ttyACM0, COM1, etc.

    :Keyword Arguments:


    """
    
    ResetSleepDt = 0.0
    Baudrate = 115200

    def __init__(self, port, timeout=10.0, debug=False):
        """ Constructor
        """
        params = {'baudrate': self.Baudrate, 'timeout': timeout}
        super(Potentiostat,self).__init__(port,**params)
        time.sleep(self.ResetSleepDt)
        atexit.register(self.atexit_cleanup)
        while self.inWaiting() > 0:
            val = self.read()
        self.hw_variant = self.get_hardware_variant()
        self.test_running = False


    def get_hardware_variant(self):
        """Returns a string representing the hardware variant.
        
        """
        cmd_dict = {CommandKey: GetVariantCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VariantKey]


    def stop_test(self):
        """Stops (any) currently running tests.

        """
        cmd_dict = {CommandKey: StopTestCmd}
        msg_dict = self.send_cmd(cmd_dict)


    def get_volt(self):
        """Returns the output voltage setting, i.e, the potential between the working and reference electrode. 

        """
        cmd_dict = {CommandKey: GetVoltCmd}
        msg_dict = self.send_cmd(cmd_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt


    def set_volt(self,volt):
        """Sets the output voltage setting, i.e., the potential between the working and reference electrode. 

        """
        cmd_dict = {CommandKey: SetVoltCmd, VoltKey: volt}
        msg_dict = self.send_cmd(cmd_dict)
        volt = msg_dict[ResponseKey][VoltKey]
        return volt


    def get_curr(self):
        """Returns and immediate measurement of electrical current flowing in/out of the working electrode. 

        """
        cmd_dict = {CommandKey: GetCurrCmd}
        msg_dict = self.send_cmd(cmd_dict)
        curr = msg_dict[ResponseKey][CurrKey]
        return curr


    def get_ref_volt(self):
        """Returns the measurement of the potential between the working and reference electrode. 

        """
        cmd_dict = {CommandKey: GetRefVoltCmd}
        msg_dict = self.send_cmd(cmd_dict)
        volt = msg_dict[ResponseKey][RefVoltKey]
        return volt


    def get_param(self,testname):
        """Returns the current values of the parameters for the specified voltammetric test. 

        """
        cmd_dict = {CommandKey: GetParamCmd, TestKey: testname} 
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][ParamKey]


    def set_param(self,testname,param):
        """Sets the parameters for the specified voltammetric test.

        """
        cmd_dict = {CommandKey: SetParamCmd, TestKey: testname, ParamKey: param}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][ParamKey]


    def set_volt_range(self,volt_range):
        """Sets the output voltage range (V)- used when setting output voltage manually.

        """
        if not volt_range in self.get_all_volt_range():
            raise ValueError('unknown voltage range')
        cmd_dict = {CommandKey: SetVoltRangeCmd, VoltRangeKey: volt_range}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VoltRangeKey]


    def get_volt_range(self):
        """Gets the current value for the output voltage range (V).

        """
        cmd_dict = {CommandKey: GetVoltRangeCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VoltRangeKey]

    def get_all_volt_range(self):
        """Gets a list of voltage ranges supported by the device.

        """
        return VoltRangeList

    def set_curr_range(self,curr_range):
        """Sets the measurement current range (uA).

        """
        if not curr_range in self.get_all_curr_range(): 
            raise ValueError('unknown current range')
        cmd_dict = {CommandKey: SetCurrRangeCmd, CurrRangeKey: curr_range}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][CurrRangeKey]


    def get_curr_range(self):
        """Gets the current value of the measurement current range (uA).

        """
        cmd_dict = {CommandKey: GetCurrRangeCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][CurrRangeKey]

    def get_all_curr_range(self):
        """Gets a list of all current ranges supported by the device.

        """
        return HwVariantToCurrRangeList[self.hw_variant]

    def get_device_id(self):
        """Gets the current value of the device identification number

        """
        cmd_dict = {CommandKey: GetDeviceIdCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][DeviceIdKey]


    def set_device_id(self,device_id):
        """Sets the current value of the device identification number.

        """
        cmd_dict = {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][DeviceIdKey]


    def set_sample_period(self,sample_period):
        """Sets the sample period (s) used for measurements. The sample period is the
        time between samples. 

        """
        cmd_dict = {CommandKey: SetSamplePeriodCmd, SamplePeriodKey: sample_period}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][SamplePeriodKey]


    def get_sample_period(self):
        """Gets the current value for the sample period (s). The sample period is the
        time between samples.

        """
        cmd_dict = {CommandKey: GetSamplePeriodCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][SamplePeriodKey]


    def set_sample_rate(self,sample_rate):
        """Sets the measurement sample rate (Hz). Note, this is an alternative way to set 
        the sample period. 

        """
        sample_period = int(1.0e3/sample_rate)
        return self.set_sample_period(sample_period)


    def get_sample_rate(self):
        """Gets the measurement sample period (Hz). Note, the sample rate is 1/sample_period.

        """
        sample_period = self.get_sample_period()
        sample_rate = 1.0e3/sample_period
        return sample_rate


    def get_test_done_time(self, test, timeunit='ms'):
        """Gets the time in seconds required to complete the specified test including any quietTime, etc. 

        """
        cmd_dict = {CommandKey: GetTestDoneTimeCmd, TestKey: test}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][TestDoneTimeKey]*TimeUnitToScale[timeunit]


    def get_test_names(self):
        """Gets the list of the names of all tests which can be performed by the device with the current firmware. 

        """
        cmd_dict = {CommandKey: GetTestNamesCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][TestNameArrayKey]


    def get_firmware_version(self):
        """Gets the version string for the firmware on the device.

        """
        cmd_dict = {CommandKey: GetVersionCmd}
        msg_dict = self.send_cmd(cmd_dict)
        return msg_dict[ResponseKey][VersionKey]


    def run_test(self, testname, param=None, filename=None, display='pbar', timeunit='s'):
        """Runs the test with specified test name and returns the time, voltage and current data.

        """
        if timeunit not in TimeUnitToScale:
            raise RuntimeError('uknown timeunit option {0}'.format(timeunit))
        if display not in (None, 'pbar', 'data'):
            raise RuntimeError('uknown display option {0}'.format(display))

        if param is not None:
            self.set_param(testname,param)

        if display in ('pbar', 'data'):
            print()
            print('test: {0}'.format(testname))
            print()
            display_print = True
        else:
            display_print = False

        if display == 'pbar':
            test_done_tval = self.get_test_done_time(testname, timeunit=timeunit)
            widgets = [progressbar.Percentage(),progressbar.Bar()]
            pbar = progressbar.ProgressBar(widgets=widgets,maxval=test_done_tval)
            pbar.start()

        tval_list = [] 
        volt_list = [] 
        curr_list = []

        if filename is not None:
            fid = open(filename,'w')

        cmd_dict = {CommandKey: RunTestCmd, TestKey: testname}
        msg_dict = self.send_cmd(cmd_dict)
        self.test_running = True

        done = False
        while not done:

            # Get dat from device
            sample_json = self.readline()
            sample_json = sample_json.strip()
            sample_dict = json.loads(sample_json.decode())

            if len(sample_dict) > 0:
                tval = sample_dict[TimeKey]*TimeUnitToScale[timeunit]
                volt = sample_dict[VoltKey]
                curr = sample_dict[CurrKey]
                tval_list.append(tval)
                volt_list.append(volt)
                curr_list.append(curr)
                # Write data to file
                if filename is not None:
                    fid.write('{0:1.3f}, {1:1.4f}, {2:1.4f}\n'.format(tval,volt,curr))
                # Handle diplay options
                if display == 'data':
                    print('{0:1.3f}, {1:1.4f}, {2:1.4f}'.format(tval,volt,curr))
                elif display == 'pbar':
                    pbar.update(tval)
            else:
                done = True

        self.test_running = False

        if display_print:
            print()
            print()

        if filename is not None:
            fid.close()

        return tval_list, volt_list, curr_list 


    def send_cmd(self,cmd_dict):
        """Sends a command to the device.  Low-level method - command is specified 
        using command dictionary.

        """
        cmd_json = json.dumps(cmd_dict) + '\n'
        self.write(cmd_json.encode())
        msg_json = self.readline()
        msg_json = msg_json.strip()
        msg_dict = json.loads(msg_json.decode())
        self.check_cmd_msg(cmd_dict,msg_dict)
        return msg_dict


    def check_cmd_msg(self,cmd_dict,msg_dict):
        self.check_for_success(msg_dict)
        self.check_cmd_match(cmd_dict,msg_dict)
        if TestKey in cmd_dict:
            self.check_test_match(cmd_dict,msg_dict)


    def check_for_success(self,msg_dict):
        try: 
            success = msg_dict[SuccessKey] 
        except KeyError:
            print('msg_dict: {0}'.format(msg_dict))
            raise IOError('json key {0} missing'.format(SuccessKey))
        if not success: 
            raise IOError('{0}, {1}'.format(msg_dict[MessageKey], msg_dict))


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


    def atexit_cleanup(self):
        if self.isOpen() and self.test_running:
            self.stop_test()









