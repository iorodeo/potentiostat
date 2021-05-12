from potentiostat import Potentiostat
import sys
import matplotlib.pyplot as plt

port = '/dev/ttyACM0'

num_pulse = 25  # Number of pulses (max = 25)
lo_pulse = (500, -0.5)  # Low  pulse,  500ms @ -0.5V
hi_pulse = (2000, 0.7)  # High pulse, 2000ms @  0.7V

dev = Potentiostat(port)
hw_variant = dev.get_hardware_variant()

dev.set_curr_range('100uA')
dev.set_sample_rate(300)

step_list = []

# Add pulses to step list
for i in range(num_pulse):
    step_list.append(lo_pulse)
    step_list.append(hi_pulse)


# Test name and test parameters
test_name = 'multiStep'
test_param = {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'step'       : step_list,
        }

dev.set_param(test_name,test_param)
t,volt,curr = dev.run_test(test_name,display='pbar')

volt_ax = plt.subplot(2,1,1)
plt.plot(t,volt)
plt.ylabel('potential (V)')
plt.grid('on')

plt.subplot(2,1,2, sharex=volt_ax)
plt.plot(t,curr)
plt.ylabel('current (uA)')
plt.xlabel('t (sec)')
plt.grid('on')

plt.show()

