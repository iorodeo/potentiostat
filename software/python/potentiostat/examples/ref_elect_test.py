from __future__ import print_function
import sys
import time
from potentiostat import Potentiostat

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

num_sample = 10
sleep_dt = 1.0 

dev = Potentiostat(port)
dev.set_all_elect_connected(True)
dev.set_volt_range('5V')
dev.set_curr_range('100uA')
dev.set_ref_elect_volt_range('1V')

dev.set_volt(0.0)

volt_list = []
curr_list = []
ref_list = []

for i in range(num_sample):

    if i < num_sample/2:
        volt = -3.0
    else:
        volt =  3.0

    dev.set_volt(volt)
    curr = dev.get_curr()
    ref_volt = dev.get_ref_volt()
    print(dev.get_ref_elect_volt_range())

    volt_list.append(volt)
    curr_list.append(curr)
    ref_list.append(ref_volt)


    print('({0}/{1}) volt: {2:1.4f}, curr: {3:1.4f}, ref: {4:1.4f}'.format(i+1, num_sample, volt, curr, ref_volt))

    time.sleep(sleep_dt)


print()
print('volt_list: ', volt_list)
print('curr_list: ', curr_list)

dev.set_all_elect_connected(False)


