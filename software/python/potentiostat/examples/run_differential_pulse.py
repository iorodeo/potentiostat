import numpy as np
import matplotlib.pyplot as plt
from potentiostat import Potentiostat

port = '/dev/ttyACM0'            # Serial port for potentiostat device
datafile = 'data.txt'            # Output file for time, curr, volt data
test_name = 'differentialPulse'  # The name of the test to run
curr_range = '10uA'              # The name of the current range [-100uA, +100uA]
sample_rate = 5.0                # The number of samples/second to collect


# Create dictionary of waveform parameters squarewave annodic stripping
test_param = {
        'quietValue' : -0.4,
        'quietTime'  :  500,
        'amplitude'  :  0.2,
        'startValue' : -0.2,
        'finalValue' :  0.2,
        'stepValue'  :  0.005,
        'window'     :  0.2,
        }

# Create potentiostat object and set current range, sample rate and test parameters
dev = Potentiostat(port,timeout=20)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)
dev.set_param(test_name,test_param)

t_done = dev.get_test_done_time(test_name)

# Run cyclic voltammetry test
t,volt,curr = dev.run_test(test_name,display='pbar',filename=datafile)


# Convert values to np arrays
print(t_done)
t = np.array(t)
volt = np.array(volt)
curr = np.array(curr)

print(t)
print(volt)
print(curr)

# Remove values during quiet time
ind = t > test_param['quietTime']*1.0e-3
t, volt, curr  = t[ind], volt[ind], curr[ind]
t = t - t[0]

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
ymin = min(curr.min(), 0)
ymax = max(curr.max(), 0)
dy = ymax - ymin
ymax += 0.1*dy
ymin -= 0.1*dy
plt.ylim(ymin, ymax)
plt.grid('on')

plt.figure(2)
plt.plot(volt,curr)
plt.xlabel('potential (V)')
plt.ylabel('current (uA)')
plt.ylim(ymin, ymax)
plt.grid('on')

plt.show()

