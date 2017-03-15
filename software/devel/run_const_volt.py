from potentiostat import Potentiostat

dev = Potentiostat('/dev/ttyACM0')
dev.set_hardware_variant('nanoAmp')
dev.set_curr_range('60nA')

test_name  =  'constant'

test_param = {
        'value'      : 0.5,   # V
        'duration'   : 5000,  # ms
        'quietTime'  : 2000,  # ms
        }

dev.set_param(test_name,test_param)

t,volt,curr = dev.run_test(test_name)

