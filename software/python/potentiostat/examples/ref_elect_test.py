from __future__ import print_function
import sys
import time
from potentiostat import Potentiostat

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

num_sample = 10
sleep_dt = 0.1 


range_value_list = [
        (0.75, '1V'),
        (1.75, '2V'),
        (4.75, '5V'),
        (7.5,  '10V')
        ]


while True:
    for val, rng in range_value_list:
        print(f'val: {val}, rng: {rng}')

        dev = Potentiostat(port)
        dev.set_all_elect_connected(True)
        dev.set_volt_range(rng)
        dev.set_curr_range('1000uA')
        dev.set_ref_elect_volt_range(rng)
        
        dev.set_volt(0.0)
        
        volt_list = []
        curr_list = []
        ref_list = []
        
        for i in range(num_sample):
        
            if i < num_sample/2:
                volt = -val
            else:
                volt = val 
        
            dev.set_volt(volt)
            curr = dev.get_curr()
            ref_volt = dev.get_ref_volt()
        
            volt_list.append(volt)
            curr_list.append(curr)
            ref_list.append(ref_volt)
        
        
            print('({0}/{1}) volt: {2:1.4f}, curr: {3:1.4f}, ref: {4:1.4f}'.format(i+1, num_sample, volt, curr, ref_volt))
        
            time.sleep(sleep_dt)
        
        
        print()
        print('volt_list: ', volt_list)
        print('curr_list: ', curr_list)
        
        dev.set_all_elect_connected(False)


