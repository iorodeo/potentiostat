.. _json_ref:

############################
JSON Serial Commands
############################

All messages sent between the Rodeostat and the host PC are sent as serialized
JSON.  This section provides a brief introduction to to these commands and the
associated responses to the command returned by the device. 

.. note::

    The Potentiostat class provides a high level interface implementing this
    protocol - so you don't need to know the details of the JSON serial
    commands in order to use the Rodeostat with Python. We provide the details
    here in order ot enable a more complete understand of how the device
    functions and to assist those who wishing to develop their own custom
    programming interfaces with the Rodeostat. 

The basic form of the commands sent from the host PC to the Rodeostat are JSON
objects with the key "command" whose value specifies the name of the command.
Additional arguments, which are specific to the command, are given as key/value
pairs. The names and number of the required additional arguments are specific 
to each command. 


.. code-block:: json

    {"command": "command name", "arg1": "val1", "arg2": "val2"}

The response from the device, in turn, is a JSON object containing a key named
"success" whose value is a boolean specifying whether or not the command was
successful. If the command was successful the boolean value will be true and
the object will contain a key named "response" whose value contains the
response from the device. The response itself consists of a number of key/value
pairs which are specific to the command. However, reposonse will always contain
the key "command" whose value specifies the name of the command generating the
response. 

.. code-block:: json

    {"success": true, "response", {"command": "command name", "key1": "val1", "key2": "val2"}}


On the other hand if the command was unsuccessful the boolean value will be
false and the object will contain the key "message" whose value contains an
error message from the device. 

.. code-block:: json

    {"success": false, "message": "error message from device", "response": {}}





List of commands
################

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
    
    .. code-block:: 
    
        {CommandKey: GetVoltCmd}

    Example command:

    .. code-block:: json

        {"command":"getVolt"}

    Response:

    .. code-block:: json

        {"success":true,"response":{"command":"getVolt","v":-0.000244}}

setVolt
    Sets the output voltage setting, i.e., the potential between the working
    and reference electrode. 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetVoltCmd, VoltKey: volt}

    Example command:

    .. code-block:: json

        {"command":"setVolt", "v": 0.5}

    Example response:

    .. code-block:: json

        {"success":true,"response":{"command":"setVolt","v":0.499878}}

getCurr
    Gets an immediate measurement of the working electrode current. 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetCurrCmd}

    Example command:

    .. code-block:: json

        {"command": "getCurr"}

    Example response:

    .. code-block:: json

        {"success":true,"response":{"command":"getCurr","i":-0.095238}}


getRefVolt
    Gets an immediate measurement of the potential between the working and
    reference electrode. 

    Form: 
    .. code-block:: 
        
        {CommandKey: GetRefVoltCmd}

    Example command:
    
    .. code-block:: json

        {"command": "getRefVolt"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getRefVolt","r":0.761661}}


getParam
    Returns the current values of the parameters for the specified
    voltammetric test. 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetParamCmd, TestKey: testname} 

    Example command:

    .. code-block:: json
    
        {"command": "getParam", "test": "cyclic"}

    Example response:
    
    .. code-block:: json
    
        { 
            "success":true,
            "response": {
                "command":"getParam",
                "test":"cyclic",
                "param":{
                    "quietValue":0,
                    "quietTime":0,
                    "amplitude":1,
                    "offset":0,
                    "period":1000,
                    "numCycles":10,
                    "shift":0 
                }
            }
        }

setParam
    Sets the parameters for the specified voltammetric test.

    Form: 
    
    .. code-block:: 

        {CommandKey: SetParamCmd, TestKey: testname, ParamKey: param}

    Example command: 
    
    .. code-block:: json
    
        {
            "command": "setParam",  
            "test": "cyclic",  
            "param": {
                "quietValue": -0.1,
                "quietTime": 1000,
                "amplitude": 1.5,
                "offset": 0,
                "period": 1000,
                "numCycles": 10,
                "shift": 0
            }
        }

    Example response:
    
    .. code-block:: json
    
        {
            "success": true,
            "response": {
                "command": "setParam",
                "test": "cyclic",
                "param": {
                    "quietValue": -0.1,
                    "quietTime": 1000,
                    "amplitude": 1.5,
                    "offset": 0,
                    "period": 1000,
                    "numCycles": 10, 
                    "shift": 0
                }
            }
        }


setVoltRange
    Sets the output voltage range (V)- used when setting output voltage
    manually.

    Form: 

    .. code-block:: 

        {CommandKey: SetVoltRangeCmd, VoltRangeKey: volt_range} 

    Example command:
    
    .. code-block:: json
    
        {"command":"setVoltRange", "voltRange": "2V"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setVoltRange","voltRange":"2V"}}


getVoltRange
    Gets the current value for the output voltage range (V).

    Form: 
    
    .. code-block:: 
        
        {CommandKey: GetVoltRangeCmd}

    Example command:
    
    .. code-block:: json
    
        {"command":"getVoltRange"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getVoltRange","voltRange":"2V"}}


setCurrRange
    Sets the range setting for measuring working electrode (uA).

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetCurrRangeCmd, CurrRangeKey: curr_range}

    Example command:
    
    .. code-block:: json
    
        {"command":"setCurrRange", "currRange": "100uA"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setCurrRange","currRange":"100uA"}}


getCurrRange:
    Gets the device's range setting for measuring working electrode current (uA).

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetCurrRangeCmd}

    Example command:
    
    .. code-block:: json
    
        {"command":"getCurrRange"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getCurrRange","currRange":"100uA"}}


getDeviceId
    Gets the current value of the device identification number

    Form: 
    
    .. code-block:: 

        {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}

    Example command:
    
    .. code-block:: json
    
        {"command":"getDeviceId"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getDeviceId","deviceId":0}}


setDeviceId
    Sets the current value of the device identification number.

    Form: 
    
    .. code-block:: 

        {CommandKey: SetDeviceIdCmd, DeviceIdKey: device_id}

    Example command:
    
    .. code-block:: json
    
        {"command":"setDeviceId", "deviceId": 1}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setDeviceId","deviceId":1}}


setSamplePeriod
    Sets the sample period (ms) used for measurements. The sample period is
    the time between samples. 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetSamplePeriodCmd, SamplePeriodKey: sample_period}

    Example command:
    
    .. code-block:: json
    
        {"command":"setSamplePeriod", "samplePeriod": 20}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setSamplePeriod","samplePeriod":20}}


getSamplePeriod
    Gets the current value for the sample period (ms). The sample period is
    the time between samples.

    Form: 
    
    .. code-block:: 

        {CommandKey: GetSamplePeriodCmd}

    Example command:
    
    .. code-block:: json
    
        {"command":"getSamplePeriod"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getSamplePeriod","samplePeriod":20}}


getTestDoneTime
    Gets the time in milliseonds required to complete the specified test including
    any quietTime, etc. 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetTestDoneTimeCmd, TestKey: test}

    Example command:
    
    .. code-block:: json
    
        {"command": "getTestDoneTime", "test": "cyclic"}

    Example response:
    
    .. code-block:: json
    
        {
            "success": true,
            "response": {
                "command": "getTestDoneTime",
                "test": "cyclic",
                "testDoneTime": 11000
            }
        }


getTestNames
    Gets the list of the names of all tests which can be performed by the
    device with the current firmware. 

    Form: 
    
    .. code-block:: 

        {CommandKey: GetTestNamesCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getTestNames"}

    Example response:
    
    .. code-block:: json
    
        {
            "success": true,
            "response": {
                "command": "getTestNames",
                "testNames": ["cyclic","sinusoid","constant","squareWave","linearSweep","chronoamp","multiStep"]
            }
        }


getVersion
    Gets the version string for the firmware on the device.

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetVersionCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getVersion"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getVersion","version":"FW0.0.9"}}


getHardwareVersion 
    Returns string representing the hardware version.

    Form: 
     
    .. code-block:: 
     
        {CommandKey: GetHardwareVersionCmd}

    Example command:
     
    .. code-block:: json
     
        {"command": "getHardwareVersion"}

    Example response:
     
    .. code-block:: json
     
        {"success":true,"response":{"command":"getHardwareVersion","version":"V0.2"}}


setRefElectConnected
    Sets the connected state (True/False) of the reference electrode.  This
    feature requires hardware version >= HW0.2

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetRefElectConnCmd, ConnectedKey: value}

    Example command:
    
    .. code-block:: json
    
        {"command": "setRefElectConnected", "connected": true}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setRefElectConnected","connected":true}}


getRefElectConnected
    Gets the connected state (True/False) of the reference electrode.  This
    feature requires hardware version >= HW0.2

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetRefElectConnCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getRefElectConnected"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getRefElectConnected","connected":true}}



setCtrElectConnected
    Sets the connected state (True/False) of the counter electrode.  This
    feature requires hardware version >= HW0.2

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetCtrElectConnCmd, ConnectedKey: value}

    Example command:
    
    .. code-block:: json
    
        {"command": "setCtrElectConnected", "connected": true}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setCtrElectConnected","connected":true}}


getCtrElectConnected
    Gets the connected state (True/False) of the counter electrode.  This
    feature requires hardware version >= HW0.2

    Form:  
    
    .. code-block:: 
    
        {CommandKey: GetCtrElectConnCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getCtrElectConnected"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getCtrElectConnected","connected":true}}


setWrkElectConnected
    Sets the connected state (True/False) of the working electrode.  This
    feature requires hardware version >= HW0.2

    Form:  
    
    .. code-block:: 
    
        {CommandKey: SetWrkElectConnCmd, ConnectedKey: value}

    Example command:
    
    .. code-block:: json
    
        {"command": "setWrkElectConnected", "connected": true}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setWrkElectConnected","connected":true}}


getWrkElectConnected
    Gets the connected state (True/False) of the working electrode.  This
    feature requires hardware version >= HW0.2

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetWrkElectConnCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getWrkElectConnected"}

    Example resposnse:
    
    .. code-block:: json
    
        {"command": "getWrkElectConnected"}


setAllElectConneced
    Sets the connected state (True/False) of all the electrodes (referene,
    counter and working). This feature requires hardware version >= HW0.2 

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetAllElectConnCmd, ConnectedKey: value}

    Example command:
    
    .. code-block:: json
    
        {"command": "setAllElectConnected", "connected": true}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setAllElectConnected","connected":true}}


getAllElectConnected
    Gets the connected state (True/False) of all the electrodes (referene,
    counter and working). Only True if all are connected. This feature
    requires hardware version >= HW0.2

    Form: 
    
    .. code-block:: 
    
        {CommandKey: GetAllElectConnCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getAllElectConnected"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getAllElectConnected","connected":true}}


setElectAutoConnect
    Set auto-connect/auto-disconnect feature. If auto-connect is set to True
    then the  ref, ctr and wrk electrodes will be automatically connected at
    the beginning of each test and automatically disconnected at the end of
    each test.

    Form: 
    
    .. code-block:: 
    
        {CommandKey: SetElectAutoConnCmd, AutoConnectKey: value}

    Example command:
    
    .. code-block:: json
    
        {"command": "setElectAutoConnect", "autoConnect": true}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setElectAutoConnect","autoConnect":true}}


getElectAutoConnect
    Gets the value of the device's auto-connect/auto-disconnect setting.

    Form: 

    .. code-block:: 
    
        {CommandKey: GetElectAutoConnCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getElectAutoConnect"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getElectAutoConnect","autoConnect":true}}


setRefElectVoltRange
    Sets the voltage range for the reference electrode analog input.

    Form: 

    .. code-block:: 
    
        {CommandKey: SetRefElectVoltRangeCmd, VoltRangeKey: volt_range}

    Example command:
    
    .. code-block:: json
    
        {"command": "setRefElectVoltRange", "voltRange": "2V"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"setRefElectVoltRange","voltRange":"2V"}}

getRefElectVoltRange
    Gets the  device's voltage range setting for the reference electrode
    analog input.  

    Form: 
    
    .. code-block:: 

        {CommandKey: GetRefElectVoltRangeCmd}

    Example command:
    
    .. code-block:: json
    
        {"command": "getRefElectVoltRange"}

    Example response:
    
    .. code-block:: json
    
        {"success":true,"response":{"command":"getRefElectVoltRange","voltRange":"5V"}}


runTest
    Runs the test with specified test name and returns the time, voltage and
    current data.

    Form: 
    
    .. code-block:: 
    
        {CommandKey: RunTestCmd, TestKey: testname}

    Example command:
    
    .. code-block:: json
    
        {"command": "runTest", "test": "cyclic"}

    Example response:

    .. code-block:: json
    
        {"success":true,"response":{"command":"runTest","test":"cyclic"}}

    followed by streaming data 

    .. code-block:: json

        {"t":20,"v":-0.1,"i":-2.799983}
        {"t":40,"v":-0.1,"i":-2.8295}
        {"t":60,"v":-0.1,"i":-2.936976}
        {"t":80,"v":-0.1,"i":-2.782137}

    ... etc

    .. code-block:: json

        {"t":10980,"v":-1.38,"i":-28.1935}
        {"t":11000,"v":-1.5,"i":-30.62896}
        {}

    An empty object marks the end of the stream


**TO DO ... MUX commands**


