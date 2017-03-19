from __future__ import print_function
from potentiostat import Potentiostat
#import matplotlib.pyplot as plt
#import scipy

curr_range = '1000uA'

port = '/dev/ttyACM0'
dev = Potentiostat(port)
dev.set_curr_range(curr_range)
dev.set_sample_period(10)

print('hardware variant: ', dev.get_hardware_variant())

if 1:
    testname = 'cyclic'
    testparam = {
            'quietValue' : 0.0,
            'quietTime'  : 1000,
            'amplitude'  : 2.0,
            'offset'     : 0.0,
            'period'     : 1000,
            'numCycles'  : 5,
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

if 0:
    testname = 'sinusoid'
    testparam = {
            'quietValue' : 0.0,
            'quietTime'  : 0,
            'amplitude'  : 2.0,
            'offset'     : 0.0,
            'period'     : 2000,
            'numCycles'  : 3,
            'shift'      : 0.0,
            }


if 0:
    testname = 'multiStep'
    step = []
    for i in range(0,10):
        step.append((1000,round(0.2*(i+1),5)))
        step.append((1000,-round(0.2*(i+1),5)))
    
    testparam = {
            'quietValue' : 0.0,
            'quietTime'  : 1000,
            'step'       : step,
            }

dev.set_param(testname,testparam)

if 1:
    t,volt,curr = dev.run_test(testname,display='pbar')
else:
    for i in range(100):
        print('cnt: ', i)
        t,volt,curr = dev.run_test(testname,display='pbar')
        print('volt_range: {0}'.format(dev.get_volt_range()))
        print('curr_range: {0}'.format(dev.get_curr_range()))
        print()


if 0:
    t = scipy.array(t)
    volt = scipy.array(volt)
    curr = scipy.array(curr)

    dt = t[1:] - t[:-1]
    print('dt.min() = {0}'.format(dt.min()))
    print('dt.max() = {0}'.format(dt.max()))

    #mask = t >= testparam['quietTime']*1.0e-3
    #t = t[mask]
    #volt = volt[mask]
    #curr = curr[mask]
    
    if dev.get_hardware_variant() == 'nanoAmp':
        curr = 1.0e3*curr
        currLabel = 'Current (nA)'
    else:
        currLabel = 'Current (uA)'
    
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
