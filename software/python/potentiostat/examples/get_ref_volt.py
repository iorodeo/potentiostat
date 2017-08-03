from __future__ import print_function
from potentiostat import Potentiostat
import sys
import time
import scipy
import matplotlib.pyplot as plt

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

num_sample = 100 
sleep_dt = 0.01 


dev = Potentiostat(port)
dev.set_volt_range('2V')

set_volt_vals = scipy.linspace(-1.9,1.9,num_sample)


out_volt_list = []
ref_volt_list = []

for i in range(num_sample):

    dev.set_volt(set_volt_vals[i])

    out_volt = dev.get_volt()
    ref_volt = dev.get_ref_volt()

    out_volt_list.append(out_volt)
    ref_volt_list.append(ref_volt)

    print('({0}/{1}) out_volt: {2}, ref_volt: {3}'.format(i+1, num_sample, out_volt, ref_volt))

    time.sleep(sleep_dt)

print()
print('out_volt_list: ', out_volt_list)
print('ref_volt_list: ', ref_volt_list)

plt.plot(out_volt_list, ref_volt_list, 'o')
plt.grid('on')
plt.xlabel('output voltage (V)')
plt.ylabel('sample voltage (V)')
plt.show()


