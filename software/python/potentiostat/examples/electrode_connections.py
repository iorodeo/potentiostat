from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

# All connected commands
print('---------------------------------------')
print('get all_connected')
rsp = dev.get_all_elect_connected()
print('rsp = ', rsp)
print()

print('set all connected = True')
rsp = dev.set_all_elect_connected(True)
print('rsp = ', rsp)
print()

print('get all_connected')
rsp = dev.get_all_elect_connected()
print('rsp = ', rsp)
print()

print('set all connected = False')
rsp = dev.set_all_elect_connected(False)
print('rsp = ', rsp)
print()

print('get all_connected')
rsp = dev.get_all_elect_connected()
print('rsp = ', rsp)
print()

# Reference electrode connection commands
print('---------------------------------------')
print('get ref elect connected')
rsp = dev.get_ref_elect_connected()
print('rsp = ', rsp)
print()

print('set ref elect connected = True')
rsp = dev.set_ref_elect_connected(True)
print('rsp = ', rsp)
print()

print('get ref elect connected')
rsp = dev.get_ref_elect_connected()
print('rsp = ', rsp)
print()

print('set ref elect connected = False')
rsp = dev.set_ref_elect_connected(False)
print('rsp = ', rsp)
print()

print('get ref elect connected')
rsp = dev.get_ref_elect_connected()
print('rsp = ', rsp)
print()


# Counter electrode connection commands
print('---------------------------------------')
print('get ctr elect connected')
rsp = dev.get_ctr_elect_connected()
print('rsp = ', rsp)
print()

print('set ctr elect connected = True')
rsp = dev.set_ctr_elect_connected(True)
print('rsp = ', rsp)
print()

print('get ctr elect connected')
rsp = dev.get_ctr_elect_connected()
print('rsp = ', rsp)
print()

print('set ctr elect connected = False')
rsp = dev.set_ctr_elect_connected(False)
print('rsp = ', rsp)
print()

print('get ctr elect connected')
rsp = dev.get_ctr_elect_connected()
print('rsp = ', rsp)
print()


# Working electrode connection commands
print('---------------------------------------')
print('get wrk elect connected')
rsp = dev.get_wrk_elect_connected()
print('rsp = ', rsp)
print()

print('set wrk elect connected = True')
rsp = dev.set_wrk_elect_connected(True)
print('rsp = ', rsp)
print()

print('get wrk elect connected')
rsp = dev.get_wrk_elect_connected()
print('rsp = ', rsp)
print()

print('set wrk elect connected = False')
rsp = dev.set_wrk_elect_connected(False)
print('rsp = ', rsp)
print()

print('get wrk elect connected')
rsp = dev.get_wrk_elect_connected()
print('rsp = ', rsp)
print()
