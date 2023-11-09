from potentiostat import Potentiostat
import sys
import time
import numpy as np
import matplotlib.pyplot as plt

# Device parameters
port = '/dev/ttyACM0' # Device port e.g. /dev/ttyACM0 (linux), COM1 (windows)
curr_range = '10uA'   # current range setting '1uA', '10uA', '100uA', '1000uA'
sample_rate = 1000.0  # sample rate for tests implemented in firmware (Hz)

# Sinusoid parameters
quiet_time = 100   # quiet time (ms)
amplitude = 0.100  # sinusoid amplitude (V)
period = 50        # sinusoid period (ms)
num_cycle = 10     # number of cycles

# Get OCP measurement parameters 
ocp_settle_dt = 1.0    # settling time prior to sampling (s)
ocp_sample_dt = 0.02   # time between samples (s)
num_ocp_samp = 100     # number of samples to average
ocp_volt_rng = '1V'    # Voltage range setting for ocp measurement

# Set up device
dev = Potentiostat(port)
dev.set_curr_range(curr_range)
dev.set_sample_rate(sample_rate)

# Set so only working and reference electrodes are connected.
dev.set_all_elect_connected(False)
dev.set_wrk_elect_connected(True)
dev.set_ref_elect_connected(True)

# Sample reference electrode to get OCP and take mean
print()
print(f'measuring OCP ... ', end='')
sys.stdout.flush()
time.sleep(ocp_settle_dt)
dev.set_ref_elect_volt_range(ocp_volt_rng)
ocp_samp = np.zeros((num_ocp_samp,))
for i in range(num_ocp_samp):
    ocp_samp[i] = dev.get_ref_volt()
    time.sleep(ocp_sample_dt)
ocp_mean = ocp_samp.mean()

print('done')
print()
print(f'ocp mean: {ocp_mean:0.3f}(V)')
print()

# Disconnect all electrodes and turn on auto connect for sinusoid test
dev.set_all_elect_connected(False)
dev.set_auto_connect(True)


# Set parameters for sinusoid test and run
name = 'sinusoid'
param = {
        'quietValue' : ocp_mean,
        'quietTime'  : quiet_time,
        'amplitude'  : amplitude,
        'offset'     : ocp_mean, 
        'period'     : period,
        'numCycles'  : num_cycle,
        'shift'      : 0.0,
        }

dev.set_param(name,param)
param = dev.get_param(name)
t,volt,curr = dev.run_test(name,display='pbar')

# Plot results
fig, ax = plt.subplots(2,1)
ax[0].plot(t,volt)
ax[0].set_ylabel('(V)')
ax[0].grid(True)
ax[1].plot(t,curr)
ax[1].set_ylabel('(uA)')
ax[1].set_xlabel('t (sec)')
ax[1].grid(True)
plt.show()
