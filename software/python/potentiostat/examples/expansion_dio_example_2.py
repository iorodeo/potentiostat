import time
from potentiostat import Potentiostat 
from potentiostat import ExpDioPin3, DioPinModeOutput 
from potentiostat import DioLow, DioHigh

dev = Potentiostat("/dev/ttyACM0")

firmware_version = dev.firmware_version
print(f'firmware version: {firmware_version}')
print()

rsp = dev.set_dio_pin_mode(ExpDioPin3,  DioPinModeOutput)
print(f'pin mode: {rsp}')
print()

rsp = dev.get_dio_pin_mode(ExpDioPin3)
print(f'pin mode: {rsp}')
print()

for i in range(10):

    # Set pin High
    rsp = dev.set_dio_value(ExpDioPin3, DioHigh)
    print(f'pin value: {rsp}')
    rsp = dev.get_dio_value(ExpDioPin3)
    print(f'pin value: {rsp}')
    print()
    time.sleep(1.0)
    
    # Set pin Low
    rsp = dev.set_dio_value(ExpDioPin3, DioLow)
    print(f'pin value: {rsp}')
    rsp = dev.get_dio_value('ExpDioPin3')
    print(f'pin value: {rsp}')
    print()
    time.sleep(1.0)



