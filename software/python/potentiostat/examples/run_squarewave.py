from potentiostat import Potentiostat
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'       # Serial port for potentiostat device
datafile = 'data.txt'       # Output file for time, curr, volt data
test_name = 'squareWave'    # The name of the test to run
curr_range = '10uA'         # The name of the current range [-100uA, +100uA]
sample_rate = 20.0          # The number of samples/second to collect


# Create dictionary of waveform parameters for cyclic voltammetry test
test_param = {
        'quietValue' :  -0.3,
        'quietTime'  :  10000,
        'amplitude'  :  0.05,
        'startValue' : -0.3,
        'finalValue' :  0.3,
        'stepValue'  :  0.005,
        'window'     : 0.2,
        }

# Create potentiostat object and set current range, sample rate and test parameters
dev = Potentiostat(port,timeout=20)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)
dev.set_param(test_name,test_param)

param = dev.get_param(test_name)

print param

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

#plt.figure(2)
#plt.plot(volt,curr)
#plt.xlabel('potential (V)')
#plt.ylabel('current (uA)')
#plt.grid('on')

plt.show()

