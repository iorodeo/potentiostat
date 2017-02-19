from __future__ import print_function
import pstat_serial

port = '/dev/ttyACM0'
dev = pstat_serial.PStatSerial(port)

#test_list = ['constant', 'cyclic', 'sinusoid', 'linearSweep', 'chronoamp', 'multiStep']

const_param = {
        "quietValue" : 2.0,
        "quietTime"  : 2000,
        "value"      : 4.0,
        "duration"   : 5000,
        }


test_list = [
        ('constant',const_param), 
        ] 


for test, param in test_list:

    cmd_dict = {'cmd':'setParam','test':test, 'param': param}
    print(cmd_dict)
    rsp_dict = dev.send_cmd(cmd_dict)
    print('test =', test)
    print('resp =', rsp_dict)
    print()

    cmd_dict = {'cmd':'getParam', 'test':test}
    rsp_dict = dev.send_cmd(cmd_dict)
    print('test =', test)
    print('resp =', rsp_dict)
    print()
    print()


