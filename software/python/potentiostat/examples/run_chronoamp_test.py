from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)
dev.set_curr_range('100uA')
dev.set_sample_period(10)

name = 'chronoamp'
param = {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'step'       : [(1000,-0.25), (1000,0.5)],
        }

dev.set_param(name,param)
t,volt,curr = dev.run_test(name,display='pbar')
