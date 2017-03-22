from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

# Get list of all test names
test_names = dev.get_test_names()

# Get parameters for each test
for test in test_names:
    rsp_dict = dev.get_param(test)
    print('test =', test)
    print('rsp  =', rsp_dict)
    print()













