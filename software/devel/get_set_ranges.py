from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

new_volt_range = "10V"
new_curr_range = "1uA"

volt_range = dev.get_volt_range()
print('volt range: {0}'.format(volt_range))

volt_range = dev.set_volt_range(new_volt_range)
print('volt range: {0}'.format(volt_range))

volt_range = dev.get_volt_range()
print('volt range: {0}'.format(volt_range))
print()


curr_range = dev.get_curr_range()
print('volt range: {0}'.format(curr_range))

curr_range = dev.set_curr_range(new_curr_range)
print('volt range: {0}'.format(curr_range))

curr_range = dev.get_curr_range()
print('volt range: {0}'.format(curr_range))
print()

