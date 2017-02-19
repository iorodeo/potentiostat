from __future__ import print_function
import pstat_serial

port = '/dev/ttyACM0'
dev = pstat_serial.PStatSerial(port)

#test_list = ['constant', 'cyclic', 'sinusoid', 'linearSweep', 'chronoamp', 'multiStep']

const_param = {
        'quietValue' : 2.0,
        'quietTime'  : 2000,
        'value'      : 4.0,
        'duration'   : 5000,
        }

cyclic_param = {
        'quietValue' : 0.2,
        'quietTime'  : 1500,
        'amplitude'  : 1.5,
        'offset'     : 0.1,
        'period'     : 2000,
        'numCycles'  : 5,
        'shift'      : 0.12,
        }

sinusoid_param = {
        'quietValue' : -0.2,
        'quietTime'  : 2500,
        'amplitude'  : 2.5,
        'offset'     : 0.7,
        'period'     : 4000,
        'numCycles'  : 6,
        'shift'      : 0.23,
        }

linearSweep_param = {
        'quietValue' : 0.6,
        'quietTime'  : 3500,
        'startValue' : -2.2,
        'finalValue' : 3.3,
        'duration'   : 3200,
        }


test_list = [
        ('constant',    const_param), 
        ('cyclic',      cyclic_param),
        ('sinusoid',    sinusoid_param),
        ('linearSweep', linearSweep_param),
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


