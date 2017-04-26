import matplotlib.pyplot as plt
import os.path
from potentiostat import Potentiostat

port = '/dev/ttyACM0'       

test_name = 'cyclic'        
curr_range = '100uA'      
sample_rate = 100.0      


test_param = {
        'quietValue' : 0.0,   # quiet period voltage (V) 
        'quietTime'  :   0,   # quiet period duration (ms)
        'amplitude'  :  0.5,   # waveform peak amplitude (V) 
        'offset'     :  0.0,   # waveform offset (V)
        'period'     : 2000,   # waveform period (ms)
        'numCycles'  :    1,   # number of cycles
    }

shift_list = [0.0, 0.25]

dev = Potentiostat(port)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)

for shift in shift_list:

    datafile = 'data_shift_{0:02}.txt'.format(int(100*shift))

    test_param['shift'] = shift
    
    t,volt,curr = dev.run_test(test_name,param=test_param,display='pbar',filename=datafile)
    
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

plt.show()

