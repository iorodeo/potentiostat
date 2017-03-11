from __future__ import print_function
from potentiostat import Potentiostat
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'
dev = Potentiostat(port)

dev.set_curr_range('100uA')

testname = 'cyclic'

param = {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'amplitude'  : 2.0,
        'offset'     : 0.0,
        'period'     : 1000,
        'numCycles'  : 3,
        'shift'      : 0.25,
        }

dev.set_param(testname,param)

t,volt,curr = dev.run_test(testname)

curr_range = dev.get_curr_range()

print()
print('curr_range: {0}'.format(curr_range))

plt.figure(1)
plt.subplot(211)
plt.plot(t,volt)
plt.ylabel('Potential (V)')
plt.grid('on')

plt.subplot(212)
plt.plot(t,curr)
plt.xlabel('time (sec)')
plt.ylabel('Current (uA)')
plt.grid('on')

plt.figure(2)
plt.plot(volt,curr)
plt.ylabel('Current (uA)')
plt.ylabel('Potential (V)')
plt.grid('on')

plt.show()
