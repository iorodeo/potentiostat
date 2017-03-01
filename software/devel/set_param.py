from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

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
        'amplitude'  : 1.52243432,
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


step = []
for i in range(0,10):
    step.append(((i+1)*1000,round(0.2*(i+1),5)))

multiStep_param = {
        'quietValue' : 2.26,
        'quietTime'  : 3550,
        'step'       : step,
        }

chronoamp_param = {
        'quietValue' : -2.26,
        'quietTime'  : 4550,
        'step'       : [(1234,0.11), (2345,0.22)],
        }

test_list = [
        ('constant',    const_param), 
        ('cyclic',      cyclic_param),
        ('sinusoid',    sinusoid_param),
        ('linearSweep', linearSweep_param),
        ('multiStep',   multiStep_param),
        ('chronoamp',   chronoamp_param),
        ] 

for test, param in test_list:

    print('test =', test)
    rsp_dict = dev.set_param(test,param)
    print('resp =', rsp_dict)
    print()

    rsp_dict = dev.get_param(test)
    print('test =', test)
    print('resp =', rsp_dict)
    print()
    print()


