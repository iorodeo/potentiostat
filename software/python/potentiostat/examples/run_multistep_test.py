from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)
dev.set_curr_range('100uA')
dev.set_sample_period(10)

step_list = []
for i in range(0,10):
    step_list.append((1000,round(0.2*(i+1),5)))
    step_list.append((1000,-round(0.2*(i+1),5)))

name = 'multiStep'
param = {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'step'       : step_list,
        }

dev.set_param(name,param)
t,volt,curr = dev.run_test(name,display='pbar')
