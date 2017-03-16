from __future__ import print_function
from potentiostat import Potentiostat
import matplotlib.pyplot as plt
import scipy

#hw_variant = 'nanoAmp'
hw_variant = 'normal'
curr_range = '100uA'

port = '/dev/ttyACM0'
dev = Potentiostat(port)
dev.set_hardware_variant(hw_variant)
dev.set_curr_range(curr_range)
dev.set_sample_period(10)

if 1:
    testname = 'cyclic'
    testparam = {
            'quietValue' : -0.5,
            'quietTime'  : 1000,
            'amplitude'  : 1.0,
            'offset'     : 0.0,
            'period'     : 1000,
            'numCycles'  : 2,
            'shift'      : 0.0,
            }

if 0:
    testname = 'constant'
    testparam = {
            'quietValue' : 0.0,
            'quietTime'  : 1000,
            'value'      : 1.0,
            'duration'   : 5000,
            }

dev.set_param(testname,testparam)

t,volt,curr = dev.run_test(testname,display='pbar')

t = scipy.array(t)
volt = scipy.array(volt)
curr = scipy.array(curr)

#print()
#print('curr_range: {0}'.format(dev.get_curr_range()))

if dev.get_hardware_variant() == 'nanoAmp':
    curr = 1.0e3*curr
    currLabel = 'current (nA)'
else:
    currLabel = 'current (uA)'


yaxis_oversize = 0.1

plt.figure(1)
plt.subplot(211)
plt.plot(t,volt)
plt.ylabel('Potential (V)')
plt.grid('on')

yaxis_min = volt.min() - 0.1*scipy.absolute(volt.min())
yaxis_max = volt.max() + 0.1*scipy.absolute(volt.max())
plt.ylim(yaxis_min, yaxis_max)

plt.title('Current Range: $\pm$ {0}'.format(curr_range))

plt.subplot(212)
plt.plot(t,curr)
plt.xlabel('time (sec)')
plt.ylabel(currLabel)

yaxis_min = curr.min() - 0.1*scipy.absolute(curr.min())
yaxis_max = curr.max() + 0.1*scipy.absolute(curr.max())
plt.ylim(yaxis_min, yaxis_max)
plt.grid('on')


plt.figure(2)
plt.plot(volt,curr)
plt.ylabel('Potential (V)')
plt.ylabel(currLabel)
plt.grid('on')

plt.show()
