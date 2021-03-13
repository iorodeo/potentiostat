from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

print()
auto_connect = dev.get_auto_connect()
print('get value')
print('auto connect: {}'.format(auto_connect))
print()

print('set to False')
auto_connect = dev.set_auto_connect(False)
print('auto connect: {}'.format(auto_connect))
print()

print('get value')
auto_connect = dev.get_auto_connect()
print('auto connect: {}'.format(auto_connect))
print()

print('set to True')
auto_connect = dev.set_auto_connect(True)
print('auto connect: {}'.format(auto_connect))
print()

print('get value')
auto_connect = dev.get_auto_connect()
print('auto connect: {}'.format(auto_connect))
print()

