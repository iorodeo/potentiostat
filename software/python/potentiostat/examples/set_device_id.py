from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

if len(sys.argv) > 2:
    dev_id = int(sys.argv[2])
else:
    dev_id = 0

dev = Potentiostat(port)

print('setting device id to: {0}'.format(dev_id))

rsp = dev.set_device_id(dev_id)



