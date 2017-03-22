from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)


# Set current range
# ---------------------------------------------------------------------

new_curr_range = "10uA"

curr_range = dev.get_curr_range()
print('volt range: {0}'.format(curr_range))

curr_range = dev.set_curr_range(new_curr_range)
print('volt range: {0}'.format(curr_range))

curr_range = dev.get_curr_range()
print('volt range: {0}'.format(curr_range))
print()



# Set voltage range. 
# --------------------------------------------------------------------
# Note, this is only need for manual operation as the voltage range is 
# automatically set from the parameters when running tests.

new_volt_range = "5V"
volt_range = dev.get_volt_range()
print('volt range: {0}'.format(volt_range))

volt_range = dev.set_volt_range(new_volt_range)
print('volt range: {0}'.format(volt_range))

volt_range = dev.get_volt_range()
print('volt range: {0}'.format(volt_range))
print()


