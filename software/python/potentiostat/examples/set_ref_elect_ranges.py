from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

new_volt_range = "5V"

volt_range = dev.get_ref_elect_volt_range()
print()
print('volt range: {0}'.format(volt_range))

volt_range = dev.set_ref_elect_volt_range(new_volt_range)
print('volt range: {0}'.format(volt_range))

volt_range = dev.get_ref_elect_volt_range()
print('volt range: {0}'.format(volt_range))
print()


