from __future__ import print_function
from potentiostat import Potentiostat
import scipy
import time

port = '/dev/ttyACM0'
dev = Potentiostat(port)

dt = 0.1
period = 10.0
numCycles = 1
amplitude = 0.5
offset = 0.0
duration = period*numCycles

t = scipy.linspace(0.0,duration,int(duration/dt))
v = amplitude*scipy.sin(2.0*scipy.pi*t/period) + offset
numpts = t.shape[0]

start = time.time()

for i in range(0,numpts):

    while (time.time() - start) < t[i]:
        time.sleep(0.001)

    dev.set_volt(v[i])
    volt = dev.get_volt()
    curr = dev.get_curr()

    print(t[i], v[i], volt, curr)



