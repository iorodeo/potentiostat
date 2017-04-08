from __future__ import print_function
from potentiostat import Potentiostat
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'       # Serial port for potentiostat device
datafile = 'test_data.txt'  # Output file for time, curr, volt data

test_name = 'cyclic'        # The name of the test to run
curr_range = '100uA'        # The name of the current range [-100uA, +100uA]
sample_rate = 100.0         # The number of samples/second to collect

volt_min = -0.1             # The minimum voltage in the waveform
volt_max =  1.0             # The maximum voltage in the waveform
volt_per_sec = 0.050        # The rate at which to transition from volt_min to volt_max
num_cycles = 1              # The number of cycle in the waveform

# Convert test parameters to amplitude, offset, period for triangle waveform output
amplitude = abs((volt_min - volt_max)/2.0)         # Waveform peak amplitude (V) 
offset = 0.5*(volt_max + volt_min)                 # Waveform offset (V) 
period_ms = int(1000*4*amplitude/volt_per_sec)     # Waveform period in (ms)
shift = 0.0                                        # Waveform phase shift - expressed as [0,1] number
                                                   # 0 = no phase shift, 0.5 = 180 deg phase shift, etc.

# Create dictionary of waveform parameters for cyclic voltammetry test
test_param = {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'amplitude'  : amplitude,
        'offset'     : offset,
        'period'     : period_ms,
        'numCycles'  : num_cycles,
        'shift'      : shift,
        }

# Create potentiostat object and set range, sample rate and test parameters
dev = Potentiostat(port)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)
dev.set_param(test_name,test_param)

# Run cyclic voltammetry test
t,volt,curr = dev.run_test(test_name,display='pbar',filename=datafile)

# plot results using matplotlib
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

