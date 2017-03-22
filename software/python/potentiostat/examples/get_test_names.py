from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

test_names = dev.get_test_names()
print('test names: ', test_names)

