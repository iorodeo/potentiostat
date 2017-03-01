from __future__ import print_function
import pstat_serial

port = '/dev/ttyACM0'
dev = pstat_serial.PStatSerial(port)

test_list = ['constant', 'cyclic', 'sinusoid', 'linearSweep', 'chronoamp', 'multiStep']

for test in test_list:
    rsp_dict = dev.get_param(test)
    print('test =', test)
    print('rsp  =', rsp_dict)
    print()









