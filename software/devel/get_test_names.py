from __future__ import print_function
from potentiostat import Potentiostat

port = '/dev/ttyACM0'
dev = Potentiostat(port)

test_names = dev.get_test_names()
print('test names:')
for name in test_names:
    print(' ', name)

