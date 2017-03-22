from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)


name = 'cyclic'
param = {
        'quietValue' : 0.2,
        'quietTime'  : 1500,
        'amplitude'  : 1.52243432,
        'offset'     : 0.1,
        'period'     : 2000,
        'numCycles'  : 5,
        'shift'      : 0.12,
        }

param_rsp = dev.set_param(name,param)
print(param_rsp)

