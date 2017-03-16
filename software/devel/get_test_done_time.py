from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

test_list = ['constant', 'cyclic', 'sinusoid', 'linearSweep', 'chronoamp', 'multiStep']

for test in test_list:
    done_time = dev.get_test_done_time(test)
    print('{0} {1}'.format(test, done_time))



