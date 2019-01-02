from __future__ import print_function
from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)

# Enable the multiplexer expansion hardware
rsp = dev.set_mux_enabled(True)
print('mux enabled: {0}'.format(rsp))

# Disable the multiplexer expansion hardware
rsp = dev.set_mux_enabled(False)
print('mux enabled: {0}'.format(rsp))
