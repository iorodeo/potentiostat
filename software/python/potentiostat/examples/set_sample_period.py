from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'


dev = Potentiostat(port)

period_new = 20

period_old = dev.get_sample_period()

dev.set_sample_period(period_new)

period_new_resp = dev.get_sample_period()

print('period orig:        {0}'.format(period_old))
print('period new (sent):  {0}'.format(period_new))
print('period new (resp):  {0}'.format(period_new_resp))

