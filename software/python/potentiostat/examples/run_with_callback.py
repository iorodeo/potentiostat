from potentiostat import Potentiostat
import sys

if len(sys.argv) > 1:
    port = sys.argv[1]
else:
    port = '/dev/ttyACM0'

dev = Potentiostat(port)
dev.set_curr_range('100uA')
dev.set_sample_period(10)

name = 'cyclic'
param = {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'amplitude'  : 2.0,
        'offset'     : 0.0,
        'period'     : 2000,
        'numCycles'  : 5,
        'shift'      : 0.0,
        }

dev.set_param(name,param)

def on_data_callback(chan, tval, volt, curr):
    print(f'chan: {chan}, tval: {tval}, volt: {volt}, curr: {curr}')

t,volt,curr = dev.run_test(name, on_data=on_data_callback, display=None)
