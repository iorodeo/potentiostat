from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    dev_id = int(sys.argv[1])
else:
    dev_id = 0

port = '/dev/ttyACM0'
dev = Potentiostat(port)

print('setting device id to: {0}'.format(dev_id))

rsp = dev.set_device_id(dev_id)

print('device id: {0}'.format(rsp))


