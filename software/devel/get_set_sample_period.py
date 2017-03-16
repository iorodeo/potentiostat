from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

sample_period = dev.get_sample_period()
print('sample period: {0}'.format(sample_period))

sample_period = dev.set_sample_period(50)
print('sample period: {0}'.format(sample_period))

sample_period = dev.get_sample_period()
print('sample period: {0}'.format(sample_period))
