from __future__ import print_function
from potentiostat import Potentiostat
import sys
import time

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'


channel_list = [1,7]
num_sample = 10 
sleep_dt = 0.25

dev = Potentiostat(port)
dev.set_volt_range('5V')
dev.set_curr_range('100uA')

dev.set_mux_enabled(True)
dev.set_enabled_mux_channels(channel_list)
dev.set_mux_ref_elect_connected(True)
dev.set_mux_ctr_elect_connected(True)

print()

for channel in channel_list:

    print('testing channel: ', channel)
    print('----------------------------------------------')

    dev.set_mux_wrk_elect_connected(channel)
    dev.set_volt(0.0)
    
    volt_list = []
    curr_list = []
    
    for i in range(num_sample):
    
        if i < num_sample/2:
            volt = -3.0
        else:
            volt =  3.0
    
        dev.set_volt(volt)
        time.sleep(sleep_dt)
        curr = dev.get_curr()
    
        volt_list.append(volt)
        curr_list.append(curr)
        print('({0}/{1}) volt: {2}, curr: {3}'.format(i+1, num_sample, volt,curr))

    print()
    print('volt_list: ', volt_list)
    print('curr_list: ', curr_list)
    print()
    print()

dev.disconnect_all_mux_elect()
dev.set_mux_enabled(False)


