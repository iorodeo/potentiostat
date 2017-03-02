from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)


volt = dev.set_volt(0.0)
print(volt)
volt = dev.get_volt()
print(volt)


