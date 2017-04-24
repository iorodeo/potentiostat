import matplotlib.pyplot as plt
import os.path
from potentiostat import Potentiostat

port = '/dev/ttyACM0'       
datafile = 'cyclic_test_data.txt'

test_name = 'cyclic'        
curr_range = '100uA'      
sample_rate = 100.0      

test_param = {
        'quietValue' : -0.1,   # quiet period voltage (V) 
        'quietTime'  : 1000,   # quiet period duration (ms)
        'amplitude'  :  0.6,   # waveform peak amplitude (V) 
        'offset'     :  0.5,   # waveform offset (V)
        'period'     : 2000,   # waveform period (ms)
        'numCycles'  :    2,   # number of cycles
        'shift'      :  0.0,   # unitless phase shift
    }

dev = Potentiostat(port)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)
dev.set_param(test_name,test_param)

t,volt,curr = dev.run_test(test_name,display='pbar',filename=datafile)

plt.figure(1)
plt.subplot(211)
plt.plot(t,volt)
plt.ylabel('potential (V)')
plt.grid('on')

plt.subplot(212)
plt.plot(t,curr)
plt.ylabel('current (uA)')
plt.xlabel('time (sec)')
plt.grid('on')

plt.figure(2)
plt.plot(volt,curr)
plt.xlabel('potential (V)')
plt.ylabel('current (uA)')
plt.grid('on')

plt.show()

