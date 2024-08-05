.. _json_ref:

############################
JSON Serial Commands
############################

All messages sent between the Rodeostat and the host PC are sent as serialzed
JSON.  This section provides a brief introduction to to these commands and
their reponses. 


getVariant
    Returns a string representing the hardware variant
    
    Form:
    
    .. code-block:: 

        {CommandKey: GetVariantCmd}


    Example command:

    .. code-block:: json
    
        {"command":"getVariant"}
            

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getVersion","version":"FW0.0.9"}}


stopTest
    Stops (any) currently running tests

    Form: 

    .. code-block:: 
    
        {CommandKey: StopTestCmd}

    Example command

    .. code-block:: json

        {"command":"stopTest"}

    Example response:

    .. code-block:: json

        {"success":true,"response":{"command":"stopTest"}}


getVolt
    Returns the output voltage setting, i.e, the potential between the working
    and reference electrode. 

    Form: 
    
    
    
        {CommandKey: GetVoltCmd}

    Example command:



        {"command":"getVolt"}

    Response:



        {"success":true,"response":{"command":"getVolt","v":-0.000244}}

setVolt
    Sets the output voltage setting, i.e., the potential between the working
    and reference electrode. 

    Form: 
    
    
    
        {CommandKey: SetVoltCmd, VoltKey: volt}

    Example command:



        {"command":"setVolt", "v": 0.5}

    Example response:



        {"success":true,"response":{"command":"setVolt","v":0.499878}}

getCurr

    Gets an immediate measurement of the working electrode current. 

    form: {CommandKey: GetCurrCmd}

    example command:
    {"command": "getCurr"}

    example response:
    {"success":true,"response":{"command":"getCurr","i":-0.095238}}


getRefVolt

    Gets an immediate measurement of the potential between the working and
    reference electrode. 

    form: {CommandKey: GetRefVoltCmd}

    example command:
    {"command": "getRefVolt"}

    example response:
    {"success":true,"response":{"command":"getRefVolt","r":0.761661}}


getParam

    Returns the current values of the parameters for the specified
    voltammetric test. 

    form: {CommandKey: GetParamCmd, TestKey: testname} 

    example command:
    {"command": "getParam", "test": "cyclic"}

    example response:
    {"success":true,"response":{"command":"getParam","test":"cyclic","param":{"quietValue":0,"quietTime":0,"amplitude":1,"offset":0,"period":1000,"numCycles":10,"shift":0}}}

setParam

    Sets the parameters for the specified voltammetric test.

    form: {CommandKey: SetParamCmd, TestKey: testname, ParamKey: param}

    example command: 
    {"command": "setParam",  "test":"cyclic",  "param": {"quietValue":-0.1,"quietTime":1000,"amplitude":1.5,"offset":0,"period":1000,"numCycles":10,"shift":0}}

    example response:
    {"success":true,"response":{"command":"setParam","test":"cyclic","param":{"quietValue":-0.1,"quietTime":1000,"amplitude":1.5,"offset":0,"period":1000,"numCycles":10,"shift":0}}}


setVoltRange

    Sets the output voltage range (V)- used when setting output voltage
    manually.

    form: {CommandKey: SetVoltRangeCmd, VoltRangeKey: volt_range} 

    example command:
    {"command":"setVoltRange", "voltRange": "2V"}

    example response:
    {"success":true,"response":{"command":"setVoltRange","voltRange":"2V"}}


getVoltRange

    Gets the current value for the output voltage range (V).

    form: {CommandKey: GetVoltRangeCmd}

    example command:
    {"command":"getVoltRange"}

    example response:
    {"success":true,"response":{"command":"getVoltRange","voltRange":"2V"}}


setCurrRange

    Sets the range setting for measuring working electrode (uA).

    form: {CommandKey: SetCurrRangeCmd, CurrRangeKey: curr_range}

    example command:
    {"command":"setCurrRange", "currRange": "100uA"}

    example response:
    {"success":true,"response":{"command":"setCurrRange","currRange":"100uA"}}


getCurrRange:

    Gets the device's range setting for measuring working electrode current (uA).

    form: {CommandKey: GetCurrRangeCmd}

    example command:
    {"command":"getCurrRange"}

    example response:
    {"success":true,"response":{"command":"getCurrRange","currRange":"100uA"}}


getDeviceId

    Gets the current value of the device identification number

    form: {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}

    example command:
    {"command":"getDeviceId"}

    example response:
    {"success":true,"response":{"command":"getDeviceId","deviceId":0}}


setDeviceId

    Sets the current value of the device identification number.

    form: {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}

    example command:
    {"command":"setDeviceId", "deviceId": 1}

    example response:
    {"success":true,"response":{"command":"setDeviceId","deviceId":1}}


setSamplePeriod

    Sets the sample period (ms) used for measurements. The sample period is
    the time between samples. 

    form: {CommandKey: SetSamplePeriodCmd, SamplePeriodKey: sample_period}

    example command:
    {"command":"setSamplePeriod", "samplePeriod": 20}

    example response:
    {"success":true,"response":{"command":"setSamplePeriod","samplePeriod":20}}


getSamplePeriod

    Gets the current value for the sample period (ms). The sample period is
    the time between samples.

    form: {CommandKey: GetSamplePeriodCmd}

    example command:
    {"command":"getSamplePeriod"}

    example response:
    {"success":true,"response":{"command":"getSamplePeriod","samplePeriod":20}}


getTestDoneTime

    Gets the time in milliseonds required to complete the specified test including
    any quietTime, etc. 

    form: {CommandKey: GetTestDoneTimeCmd, TestKey: test}

    example command:
    {"command": "getTestDoneTime", "test": "cyclic"}

    example response:
    {"success":true,"response":{"command":"getTestDoneTime","test":"cyclic","testDoneTime":11000}}


getTestNames

    Gets the list of the names of all tests which can be performed by the
    device with the current firmware. 

    form: {CommandKey: GetTestNamesCmd}

    example command:
    {"command": "getTestNames"}

    example response:
    {"success":true,"response":{"command":"getTestNames","testNames":["cyclic","sinusoid","constant","squareWave","linearSweep","chronoamp","multiStep"]}}


getVersion

    Gets the version string for the firmware on the device.

    form: {CommandKey: GetVersionCmd}

    example command:
    {"command": "getVersion"}

    example response:
    {"success":true,"response":{"command":"getVersion","version":"FW0.0.9"}}


getHardwareVersion

     Returns string representing the hardware version.

     form: {CommandKey: GetHardwareVersionCmd}

     example command:
     {"command": "getHardwareVersion"}

     example response:
     {"success":true,"response":{"command":"getHardwareVersion","version":"V0.2"}}


setRefElectConnected

    Sets the connected state (True/False) of the reference electrode.  This
    feature requires hardware version >= HW0.2

    form: {CommandKey: SetRefElectConnCmd, ConnectedKey: value}

    example command:
    {"command": "setRefElectConnected", "connected": true}

    example response:
    {"success":true,"response":{"command":"setRefElectConnected","connected":true}}


getRefElectConnected

    Gets the connected state (True/False) of the reference electrode.  This
    feature requires hardware version >= HW0.2

    form: {CommandKey: GetRefElectConnCmd}

    example command:
    {"command": "getRefElectConnected"}

    example response:
    {"success":true,"response":{"command":"getRefElectConnected","connected":true}}



setCtrElectConnected

    Sets the connected state (True/False) of the counter electrode.  This
    feature requires hardware version >= HW0.2

    form: {CommandKey: SetCtrElectConnCmd, ConnectedKey: value}

    example command:
    {"command": "setCtrElectConnected", "connected": true}

    example response:
    {"success":true,"response":{"command":"setCtrElectConnected","connected":true}}


getCtrElectConnected

    Gets the connected state (True/False) of the counter electrode.  This
    feature requires hardware version >= HW0.2

    form:  {CommandKey: GetCtrElectConnCmd}

    example command:
    {"command": "getCtrElectConnected"}

    example response:
    {"success":true,"response":{"command":"getCtrElectConnected","connected":true}}


setWrkElectConnected

    Sets the connected state (True/False) of the working electrode.  This
    feature requires hardware version >= HW0.2

    form:  {CommandKey: SetWrkElectConnCmd, ConnectedKey: value}

    example command:
    {"command": "setWrkElectConnected", "connected": true}

    example response:
    {"success":true,"response":{"command":"setWrkElectConnected","connected":true}}


getWrkElectConnected

    Gets the connected state (True/False) of the working electrode.  This
    feature requires hardware version >= HW0.2

    form: {CommandKey: GetWrkElectConnCmd}

    example command:
    {"command": "getWrkElectConnected"}

    example resposnse:
    {"command": "getWrkElectConnected"}


setAllElectConneced

    Sets the connected state (True/False) of all the electrodes (referene,
    counter and working). This feature requires hardware version >= HW0.2 

    form: {CommandKey: SetAllElectConnCmd, ConnectedKey: value}

    example command:
    {"command": "setAllElectConnected", "connected": true}

    example response:
    {"success":true,"response":{"command":"setAllElectConnected","connected":true}}


getAllElectConnected

    Gets the connected state (True/False) of all the electrodes (referene,
    counter and working). Only True if all are connected. This feature
    requires hardware version >= HW0.2

    form: {CommandKey: GetAllElectConnCmd}

    example command:
    {"command": "getAllElectConnected"}

    example response:
    {"success":true,"response":{"command":"getAllElectConnected","connected":true}}


setElectAutoConnect

    Set auto-connect/auto-disconnect feature. If auto-connect is set to True
    then the  ref, ctr and wrk electrodes will be automatically connected at
    the beginning of each test and automatically disconnected at the end of
    each test.

    form: {CommandKey: SetElectAutoConnCmd, AutoConnectKey: value}

    example command:
    {"command": "setElectAutoConnect", "autoConnect": true}

    example response:
    {"success":true,"response":{"command":"setElectAutoConnect","autoConnect":true}}


getElectAutoConnect

    Gets the value of the device's auto-connect/auto-disconnect setting.

    form: {CommandKey: GetElectAutoConnCmd}

    example command:
    {"command": "getElectAutoConnect"}

    example response:
    {"success":true,"response":{"command":"getElectAutoConnect","autoConnect":true}}


setRefElectVoltRange

    Sets the voltage range for the reference electrode analog input.

    form: {CommandKey: SetRefElectVoltRangeCmd, VoltRangeKey: volt_range}

    example command:
    {"command": "setRefElectVoltRange", "voltRange": "2V"}

    example response:
    {"success":true,"response":{"command":"setRefElectVoltRange","voltRange":"2V"}}

getRefElectVoltRange

    Gets the  device's voltage range setting for the reference electrode
    analog input.  

    form: {CommandKey: GetRefElectVoltRangeCmd}

    example command:
    {"command": "getRefElectVoltRange"}

    example response:
    {"success":true,"response":{"command":"getRefElectVoltRange","voltRange":"5V"}}


runTest

    Runs the test with specified test name and returns the time, voltage and
    current data.

    form: {CommandKey: RunTestCmd, TestKey: testname}

    example command:
    {"command": "runTest", "test": "cyclic"}

    example response:
    {"success":true,"response":{"command":"runTest","test":"cyclic"}}

    followed by streaming data 

    {"t":20,"v":-0.1,"i":-2.799983}
    {"t":40,"v":-0.1,"i":-2.8295}
    {"t":60,"v":-0.1,"i":-2.936976}
    {"t":80,"v":-0.1,"i":-2.782137}
    ... etc
    {"t":10980,"v":-1.38,"i":-28.1935}
    {"t":11000,"v":-1.5,"i":-30.62896}
    {}

    empty object marks end of stream

# ------------------------
# TO DO ... MUX commands
# ------------------------
    

