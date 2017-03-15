from __future__ import print_function
from potentiostat import Potentiostat
import matplotlib.pyplot as plt
import scipy

hw_variant = 'nanoAmp'
curr_range = '100nA'

port = '/dev/ttyACM0'
dev = Potentiostat(port)
dev.set_hardware_variant(hw_variant)
dev.set_curr_range(curr_range)

testname = 'cyclic'

testparam = {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'amplitude'  : 1.0,
        'offset'     : 0.0,
        'period'     : 20000,
        'numCycles'  : 2,
        'shift'      : 0.0,
        }

dev.set_param(testname,testparam)

t,volt,curr = dev.run_test(testname)

t = scipy.array(t)
volt = scipy.array(volt)
curr = scipy.array(curr)

print()
print('curr_range: {0}'.format(dev.get_curr_range()))

if dev.get_hardware_variant() == 'nanoAmp':
    curr = 1.0e3*curr
    currLabel = 'current (nA)'
else:
    currLabel = 'current (uA)'

plt.figure(1)
plt.subplot(211)
plt.plot(t,volt)
plt.ylabel('Potential (V)')
plt.grid('on')
plt.title('Current Range: $\pm$ {0}'.format(curr_range))

plt.subplot(212)
plt.plot(t,curr)
plt.xlabel('time (sec)')
plt.ylabel(currLabel)
plt.grid('on')

plt.figure(2)
plt.plot(volt,curr)
plt.ylabel('Potential (V)')
plt.ylabel(currLabel)
plt.grid('on')

plt.show()
