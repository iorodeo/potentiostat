from __future__ import print_function
from potentiostat import Potentiostat
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'
dev = Potentiostat(port)

testname = 'cyclic'

param = {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'amplitude'  : 1.52243432,
        'offset'     : 0.1,
        'period'     : 2000,
        'numCycles'  : 5,
        'shift'      : 0.0,
        }

dev.set_param(testname,param)

t,volt,curr = dev.run_test(testname)

plt.subplot(211)
plt.plot(t,volt)
plt.ylabel('Potential (V)')
plt.grid('on')

plt.subplot(212)
plt.plot(t,curr)
plt.xlabel('time (sec)')
plt.ylabel('Current (uA)')
plt.grid('on')

plt.show()
