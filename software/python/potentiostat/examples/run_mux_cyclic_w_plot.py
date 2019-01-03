from potentiostat import Potentiostat
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'       # Serial port for potentiostat device
datafile = 'data.txt'       # Output file for time, curr, volt data

channel_list = [1,7]

test_name = 'cyclic'        # The name of the test to run
curr_range = '100uA'        # The name of the current range [-100uA, +100uA]
sample_rate = 100.0         # The number of samples/second to collect

volt_min = -0.2             # The minimum voltage in the waveform (V)
volt_max =  3.0             # The maximum voltage in the waveform (V)
#volt_per_sec = 0.050        # The rate at which to transition from volt_min to volt_max (V/s)
volt_per_sec = 1.00         # The rate at which to transition from volt_min to volt_max (V/s)
num_cycles = 1              # The number of cycle in the waveform

# Convert parameters to amplitude, offset, period, phase shift for triangle waveform
amplitude = (volt_max - volt_min)/2.0            # Waveform peak amplitude (V) 
offset = (volt_max + volt_min)/2.0               # Waveform offset (V) 
period_ms = int(1000*4*amplitude/volt_per_sec)   # Waveform period in (ms)
shift = 0.0                                      # Waveform phase shift - expressed as [0,1] number
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

# Create potentiostat object and set current range, sample rate and test parameters
dev = Potentiostat(port)     
dev.set_curr_range(curr_range)   
dev.set_sample_rate(sample_rate)
dev.set_param(test_name,test_param)

dev.set_mux_enabled(True)
dev.set_enabled_mux_channels(channel_list)

# Run cyclic voltammetry test
#data_dict = dev.run_test(test_name,display='data',filename=datafile)
#data_dict = dev.run_test(test_name,display='data')
data_dict = dev.run_test(test_name,display='pbar',filename='data.txt')
#data_dict = dev.run_test(test_name,display='pbar',filename='data.pkl')

dev.set_mux_enabled(False)


# plot results using matplotlib
for chan, data in data_dict.iteritems():
    plt.figure(chan)
    plt.subplot(211)
    plt.plot(data['t'],data['v'])
    plt.ylabel('potential (V)')
    plt.grid('on')
    plt.title('volt,curr vs time, channel = {0}'.format(chan))
    
    plt.subplot(212)
    plt.plot(data['t'],data['i'])
    plt.ylabel('current (uA)')
    plt.xlabel('time (sec)')
    plt.grid('on')
    
    plt.figure(chan + len(channel_list))
    plt.plot(data['v'],data['i'])
    plt.xlabel('potential (V)')
    plt.ylabel('current (uA)')
    plt.title('curr vs volt, channel = {0}'.format(chan))
    plt.grid('on')

plt.show()

