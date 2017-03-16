from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

version = dev.get_version()
print('firmware version: ', version)
