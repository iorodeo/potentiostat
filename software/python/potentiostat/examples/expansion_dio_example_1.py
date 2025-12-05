import time
from potentiostat import Potentiostat

dev = Potentiostat("/dev/ttyACM0")

firmware_version = dev.firmware_version
print(f'firmware version: {firmware_version}')
print()

allowed_dio_pins = dev.allowed_dio_pins()
print(f'allowed dio pins: {allowed_dio_pins}')
print()

allowed_dio_pin_modes = dev.allowed_dio_pin_modes()
print(f'allowed dio pin modes: {allowed_dio_pin_modes}')
print()

rsp = dev.set_dio_pin_mode('ExpDioPin3',  'Output')
print(f'pin mode: {rsp}')
print()

rsp = dev.get_dio_pin_mode('ExpDioPin3')
print(f'pin mode: {rsp}')
print()

for i in range(10):

    # Set pin High
    rsp = dev.set_dio_value('ExpDioPin3', 'High')
    print(f'pin value: {rsp}')
    rsp = dev.get_dio_value('ExpDioPin3')
    print(f'pin value: {rsp}')
    print()
    time.sleep(1.0)
    
    # Set pin Low
    rsp = dev.set_dio_value('ExpDioPin3', 'Low')
    print(f'pin value: {rsp}')
    rsp = dev.get_dio_value('ExpDioPin3')
    print(f'pin value: {rsp}')
    print()
    time.sleep(1.0)



