from __future__ import print_function
import pstat_serial

port = '/dev/ttyACM0'
dev = pstat_serial.PStatSerial(port)

test_list = ['constant', 'cyclic', 'sinusoid', 'linearSweep', 'chronoamp', 'multiStep']

for test in test_list:
    cmd_dict = {'cmd':'getParam','test':test}
    rsp_dict = dev.send_cmd(cmd_dict)
    print('test =', test)
    print('resp =', rsp_dict)
    print()









