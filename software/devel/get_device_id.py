from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

rsp = dev.get_device_id()
print('device id: {0}'.format(rsp))
