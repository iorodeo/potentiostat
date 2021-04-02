#include "ps_system_state.h"
#include "ps_device_id_eeprom.h"
#include "util/atomic.h"


namespace ps
{

    SystemState::SystemState()
    { 
        testInProgress_ = false;
        lastSampleFlag_ = false;
        timerCnt_ = 0;
        test_ = nullptr;

        //currLowPass_.setParam(CurrLowPassParam);
        for (int i=0; i<NumMuxChan; i++)
        {
            currLowPass_.push_back(LowPass(CurrLowPassParam));
        }
        setSamplePeriod(DefaultSamplePeriod);
    }


    void SystemState::initialize()
    {
        commandTable_.setClient(this);
        commandTable_.registerMethod(CommandKey,   RunTestCmd,              &SystemState::onCommandRunTest);
        commandTable_.registerMethod(CommandKey,   StopTestCmd,             &SystemState::onCommandStopTest);
        commandTable_.registerMethod(CommandKey,   GetVoltCmd,              &SystemState::onCommandGetVolt);
        commandTable_.registerMethod(CommandKey,   SetVoltCmd,              &SystemState::onCommandSetVolt);
        commandTable_.registerMethod(CommandKey,   GetCurrCmd,              &SystemState::onCommandGetCurr);
        commandTable_.registerMethod(CommandKey,   GetRefVoltCmd,           &SystemState::onCommandGetRefVolt);
        commandTable_.registerMethod(CommandKey,   SetParamCmd,             &SystemState::onCommandSetTestParam);
        commandTable_.registerMethod(CommandKey,   GetParamCmd,             &SystemState::onCommandGetTestParam);
        commandTable_.registerMethod(CommandKey,   SetVoltRangeCmd,         &SystemState::onCommandSetVoltRange);
        commandTable_.registerMethod(CommandKey,   GetVoltRangeCmd,         &SystemState::onCommandGetVoltRange);
        commandTable_.registerMethod(CommandKey,   SetCurrRangeCmd,         &SystemState::onCommandSetCurrRange);
        commandTable_.registerMethod(CommandKey,   GetCurrRangeCmd,         &SystemState::onCommandGetCurrRange);
        commandTable_.registerMethod(CommandKey,   SetDeviceIdCmd,          &SystemState::onCommandSetDeviceId);
        commandTable_.registerMethod(CommandKey,   GetDeviceIdCmd,          &SystemState::onCommandGetDeviceId);
        commandTable_.registerMethod(CommandKey,   SetSamplePeriodCmd,      &SystemState::onCommandSetSamplePeriod);
        commandTable_.registerMethod(CommandKey,   GetSamplePeriodCmd,      &SystemState::onCommandGetSamplePeriod);
        commandTable_.registerMethod(CommandKey,   GetTestDoneTimeCmd,      &SystemState::onCommandGetTestDoneTime);
        commandTable_.registerMethod(CommandKey,   GetTestNamesCmd,         &SystemState::onCommandGetTestNames);
        commandTable_.registerMethod(CommandKey,   GetVersionCmd,           &SystemState::onCommandGetVersion);
        commandTable_.registerMethod(CommandKey,   GetVariantCmd,           &SystemState::onCommandGetVariant);
        commandTable_.registerMethod(CommandKey,   SetMuxEnabledCmd,        &SystemState::onCommandSetMuxEnabled);
        commandTable_.registerMethod(CommandKey,   GetMuxEnabledCmd,        &SystemState::onCommandGetMuxEnabled);
        commandTable_.registerMethod(CommandKey,   SetEnabledMuxChanCmd,    &SystemState::onCommandSetEnabledMuxChan);
        commandTable_.registerMethod(CommandKey,   GetEnabledMuxChanCmd,    &SystemState::onCommandGetEnabledMuxChan);
        commandTable_.registerMethod(CommandKey,   GetMuxTestNamesCmd,      &SystemState::onCommandGetMuxTestNames);
        commandTable_.registerMethod(CommandKey,   SetMuxRefElectConnCmd,   &SystemState::onCommandSetMuxRefElectConn);
        commandTable_.registerMethod(CommandKey,   GetMuxRefElectConnCmd,   &SystemState::onCommandGetMuxRefElectConn);
        commandTable_.registerMethod(CommandKey,   SetMuxCtrElectConnCmd,   &SystemState::onCommandSetMuxCtrElectConn); 
        commandTable_.registerMethod(CommandKey,   GetMuxCtrElectConnCmd,   &SystemState::onCommandGetMuxCtrElectConn);
        commandTable_.registerMethod(CommandKey,   SetMuxWrkElectConnCmd,   &SystemState::onCommandSetMuxWrkElectConn);
        commandTable_.registerMethod(CommandKey,   GetMuxWrkElectConnCmd,   &SystemState::onCommandGetMuxWrkElectConn); 
        commandTable_.registerMethod(CommandKey,   DisconnAllMuxElectCmd,   &SystemState::onCommandDisconnAllMuxElect);
#if defined HARDWARE_VERSION_0P2 
        commandTable_.registerMethod(CommandKey,   SetRefElectConnCmd,      &SystemState::onCommandSetRefElectConn);
        commandTable_.registerMethod(CommandKey,   GetRefElectConnCmd,      &SystemState::onCommandGetRefElectConn);
        commandTable_.registerMethod(CommandKey,   SetCtrElectConnCmd,      &SystemState::onCommandSetCtrElectConn);
        commandTable_.registerMethod(CommandKey,   GetCtrElectConnCmd,      &SystemState::onCommandGetCtrElectConn);
        commandTable_.registerMethod(CommandKey,   SetWrkElectConnCmd,      &SystemState::onCommandSetWrkElectConn);
        commandTable_.registerMethod(CommandKey,   GetWrkElectConnCmd,      &SystemState::onCommandGetWrkElectConn);
        commandTable_.registerMethod(CommandKey,   SetAllElectConnCmd,      &SystemState::onCommandSetAllElectConn);
        commandTable_.registerMethod(CommandKey,   GetAllElectConnCmd,      &SystemState::onCommandGetAllElectConn);
        commandTable_.registerMethod(CommandKey,   SetElectAutoConnCmd,     &SystemState::onCommandSetElectAutoConn);
        commandTable_.registerMethod(CommandKey,   GetElectAutoConnCmd,     &SystemState::onCommandGetElectAutoConn);
        commandTable_.registerMethod(CommandKey,   SetRefElectVoltRangeCmd, &SystemState::onCommandSetRefElectVoltRange);
        commandTable_.registerMethod(CommandKey,   GetRefElectVoltRangeCmd, &SystemState::onCommandGetRefElectVoltRange);
        commandTable_.registerMethod(CommandKey,   GetHardwareVersionCmd,   &SystemState::onCommandGetHardwareVersion);
#endif

        analogSubsystem_.initialize();
        analogSubsystem_.setVolt(0.0);
        messageReceiver_.reset();

#if defined HARDWARE_VERSION_0P2 
        electrodeAutoConnect_ = true;
        electrodeSwitch_.initialize();
        electrodeSwitch_.setAllConnected(false);
#endif

    }


    ReturnStatus SystemState::onCommandRunTest(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status = voltammetry_.getTest(jsonMsg,jsonDat,test_);
        if (!status.success)
        {
            return status;
        }

        if (test_ == nullptr)
        {
            status.success = false;
            status.message = String("something is wrong, test_ == nullptr");
            return status;
        }

        if (multiplexer_.isRunning())
        {
            if (!(test_ -> isMuxCompatible()))
            {
                status.success = false;
                status.message = String("test, ") + (test_ -> getName()) + String(", is not mux compatible");
                return status;
            }
            if (multiplexer_.numEnabledWrkElect() <= 0)
            {
                status.success = false;
                status.message = String("mux running, but no enabled working electrode channels");
                return status;
            }
            else
            {
                multiplexer_.connectCtrElect();
                multiplexer_.connectRefElect();
                multiplexer_.connectFirstEnabledWrkElect();
            }
        }

        startTest();
        return status;
    }


    ReturnStatus SystemState::onCommandStopTest(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        stopTest();
        return status;
    }


    ReturnStatus SystemState::onCommandGetVolt(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        float volt = analogSubsystem_.getVolt();
        jsonDat.set(VoltKey,volt);
        return status;
    }


    ReturnStatus SystemState::onCommandSetVolt(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(VoltKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + VoltKey;
            return status;
        }

        if ( !(jsonMsg[VoltKey].is<float>() || jsonMsg[VoltKey].is<long>()) )
        {
            status.success = false;
            status.message = String("unable to convert volt to float");
            return status;
        }

        float volt = 0.0;
        if (jsonMsg[VoltKey].is<float>())
        { 
            volt = jsonMsg.get<float>(VoltKey);
        }
        else 
        {
            volt = float(jsonMsg.get<long>(VoltKey));
        }

        analogSubsystem_.setVolt(volt);
        volt = analogSubsystem_.getVolt();
        jsonDat.set(VoltKey,volt);
        return status;
    }

    
    ReturnStatus SystemState::onCommandGetCurr(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        float curr = analogSubsystem_.getCurr();
        jsonDat.set(CurrKey,curr);
        return status;
    }


    ReturnStatus SystemState::onCommandGetRefVolt(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        float refVolt = analogSubsystem_.getRefElectVolt();
        jsonDat.set(RefVoltKey,refVolt);
        return status;
    }


    ReturnStatus SystemState::onCommandSetTestParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status = voltammetry_.setParam(jsonMsg,jsonDat);
        return status;
    }


    ReturnStatus SystemState::onCommandGetTestParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status = voltammetry_.getParam(jsonMsg,jsonDat);
        return status;
    }


    ReturnStatus SystemState::onCommandSetVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(VoltRangeKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + VoltRangeKey;
        }
        else
        {
            String voltRangeName = String((const char *)(jsonMsg[VoltRangeKey]));
            status = analogSubsystem_.setVoltRangeByName(voltRangeName);
            jsonDat.set(VoltRangeKey,analogSubsystem_.getVoltRangeName());
        }
        return status;
    }


    ReturnStatus SystemState::onCommandGetVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(VoltRangeKey,analogSubsystem_.getVoltRangeName());
        return status;
    }


    ReturnStatus SystemState::onCommandSetCurrRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(CurrRangeKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + CurrRangeKey;
        }
        else
        {
            String currRangeName = String((const char *)(jsonMsg[CurrRangeKey]));
            status = analogSubsystem_.setCurrRangeByName(currRangeName);
            jsonDat.set(CurrRangeKey,analogSubsystem_.getCurrRangeName());
        }
        return status;
    }


    ReturnStatus SystemState::onCommandGetCurrRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(CurrRangeKey,analogSubsystem_.getCurrRangeName());
        return status;
    }


    ReturnStatus SystemState::onCommandSetDeviceId(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        DeviceId_EEPROM deviceIdMem;
        status = deviceIdMem.set(jsonMsg,jsonDat);
        return status;
    }


    ReturnStatus SystemState::onCommandGetDeviceId(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        DeviceId_EEPROM deviceIdMem;
        deviceIdMem.get(jsonDat);
        return status;
    }

    ReturnStatus SystemState::onCommandSetSamplePeriod(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(SamplePeriodKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + SamplePeriodKey;
        }
        else
        {
            if (!jsonMsg[SamplePeriodKey].is<uint32_t>())
            {
                status.success = false;
                status.message = String("json ") + SamplePeriodKey + String(" value is not uin32_t");
            }
            else
            {
                uint32_t samplePeriodMs = jsonMsg.get<uint32_t>(SamplePeriodKey);
                uint32_t samplePeriodUs = uint32_t(convertMsToUs(samplePeriodMs));
                if (samplePeriodUs > MaximumSamplePeriod)
                {
                    status.success = false;
                    status.message = String("json ") + SamplePeriodKey + String(" value is too large");
                }
                else if (samplePeriodUs < MinimumSamplePeriod)
                {
                    status.success = false;
                    status.message = String("json ") + SamplePeriodKey + String(" value is too small");
                }
                else
                {
                    setSamplePeriod(samplePeriodUs);
                    jsonDat.set(SamplePeriodKey,convertUsToMs(getSamplePeriod()));
                }
            }
        }
        return status;
    }


    ReturnStatus SystemState::onCommandGetSamplePeriod(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(SamplePeriodKey,convertUsToMs(getSamplePeriod()));
        return status;
    }

    
    ReturnStatus SystemState::onCommandGetTestDoneTime(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = voltammetry_.getTestDoneTime(jsonMsg, jsonDat);
        return status;
    }


    ReturnStatus SystemState::onCommandGetTestNames(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = voltammetry_.getTestNames(jsonMsg, jsonDat);
        return status;
    }


    ReturnStatus SystemState::onCommandGetVersion(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(VersionKey,FirmwareVersion);
        return status;
    }


    ReturnStatus SystemState::onCommandGetVariant(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(VariantKey,HardwareVariant);
        return status;
    }

    ReturnStatus SystemState::onCommandSetMuxEnabled(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(MuxEnabledKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + MuxEnabledKey;
            return status;
        }

        if ( !(jsonMsg[MuxEnabledKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert muxEnabled to bool");
            return status;
        }

        if (jsonMsg.get<bool>(MuxEnabledKey))
        {
            multiplexer_.setupSwitchPins();
            multiplexer_.start();
        }
        else
        {
            multiplexer_.stop();
            multiplexer_.disconnectWrkElect();
            multiplexer_.disconnectRefElect();
            multiplexer_.disconnectCtrElect();
            multiplexer_.clearSwitchPins();
        }
        jsonDat.set(MuxEnabledKey,multiplexer_.isRunning());
        return status;
    }

    ReturnStatus SystemState::onCommandGetMuxEnabled(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(MuxEnabledKey,multiplexer_.isRunning());
        return status;
    }

    ReturnStatus SystemState::onCommandSetEnabledMuxChan(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status.success = true;

        if (!jsonMsg.containsKey(MuxChannelKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + MuxChannelKey;
            return status;
        }
        if (!jsonMsg[MuxChannelKey].is<JsonArray&>()) 
        {
            status.success = false;
            status.message = MuxChannelKey + String(" not a JsonArray");
            return status;
        }

        JsonArray &jsonMuxChannelArray = jsonMsg[MuxChannelKey];
        if (jsonMuxChannelArray.size() > NumMuxChan)
        {
            status.success = false;
            status.message = MuxChannelKey + String(" array too large");
            return status;
        }

        Array<int,NumMuxChan> enabledWrkElect;
        for (size_t i=0; i<jsonMuxChannelArray.size(); i++)
        {
            if (jsonMuxChannelArray[i].is<int>())
            {
                int channel = jsonMuxChannelArray.get<int>(i);
                if ((channel > 0) && (channel <= NumMuxChan))
                {
                    enabledWrkElect.push_back(channel);
                }
                else
                {
                    status.success = false;
                    status.message = MuxChannelKey + String(" element out of range");
                    break;
                }
            }
            else
            {
                status.success = false;
                status.message = MuxChannelKey + String(" element not an int");
                break;
            }
        }

        if (status.success)
        {
            multiplexer_.setEnabledWrkElect(enabledWrkElect);
            JsonArray &jsonEnabledArray = jsonDat.createNestedArray(MuxChannelKey);
            for (size_t i=0; i<enabledWrkElect.size(); i++)
            {
                jsonEnabledArray.add(enabledWrkElect[i]);
            }
        }
        return status;
    }

    ReturnStatus SystemState::onCommandGetEnabledMuxChan(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        Array<int,NumMuxChan> enabledWrkElect = multiplexer_.getEnabledWrkElect();
        JsonArray &jsonEnabledArray = jsonDat.createNestedArray(MuxChannelKey);
        for (size_t i=0; i<enabledWrkElect.size(); i++)
        {
            jsonEnabledArray.add(enabledWrkElect[i]);
        }
        return status;
    }

    ReturnStatus SystemState::onCommandGetMuxTestNames(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = voltammetry_.getMuxTestNames(jsonMsg, jsonDat);
        return status;
    } 

    ReturnStatus SystemState::onCommandSetMuxRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert ") + ConnectedKey + String(" to bool");
            return status;
        }

        if (!multiplexer_.isRunning())
        {
            status.success = false;
            status.message = String("mux not enabled - unable to connect/disconnect");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            multiplexer_.connectRefElect();
        }
        else
        {
            multiplexer_.disconnectRefElect();
        }

        jsonDat.set(ConnectedKey,multiplexer_.isConnectedRef());
        return status;
    }

    ReturnStatus SystemState::onCommandGetMuxRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (multiplexer_.isRunning())
        {
            jsonDat.set(ConnectedKey,multiplexer_.isConnectedRef());
        }
        else
        {
            jsonDat.set(ConnectedKey,false);
        }
        return status;

    }

    ReturnStatus SystemState::onCommandSetMuxCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ConnectedKey + String("' to bool");
            return status;
        }

        if (!multiplexer_.isRunning())
        {
            status.success = false;
            status.message = String("mux not enabled - unable to connect/disconnect");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            multiplexer_.connectCtrElect();
        }
        else
        {
            multiplexer_.disconnectCtrElect();
        }

        jsonDat.set(ConnectedKey,multiplexer_.isConnectedCtr());
        return status;
    }

    ReturnStatus SystemState::onCommandGetMuxCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (multiplexer_.isRunning())
        {
            jsonDat.set(ConnectedKey,multiplexer_.isConnectedCtr());
        }
        else
        {
            jsonDat.set(ConnectedKey,false);
        }
        return status;
    }

    ReturnStatus SystemState::onCommandSetMuxWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if (!multiplexer_.isRunning())
        {
            status.success = false;
            status.message = String("mux not enabled - unable to connect/disconnect");
            return status;
        }

        if ((!(jsonMsg[ConnectedKey].is<bool>())) && (!jsonMsg[ConnectedKey].is<int>()))
        {
            status.success = false;
            status.message = ConnectedKey + String(" must be bool or int");
            return status;
        }

        if (jsonMsg[ConnectedKey].is<bool>())
        {
            if (!jsonMsg.get<bool>(ConnectedKey))
            {
                multiplexer_.disconnectWrkElect();
                jsonDat.set(ConnectedKey,multiplexer_.isConnectedWrk());
            }
            else
            {
                status.success = false;
                status.message = String("if bool '") + ConnectedKey + String("' must be false");
                return status;
            }
        }
        else
        {
            int electNum = jsonMsg.get<int>(ConnectedKey);
            if ((electNum <= 0) && (electNum > NumMuxChan))
            {
                status.success = false;
                status.message = String("mux channel out of range");
                return status;
            }

            if (!multiplexer_.isWrkElectEnabled(electNum))
            {
                status.success = false;
                status.message = String("mux channel is not enabled");
                return status;
            }

            multiplexer_.connectWrkElect(electNum);
            jsonDat.set(ConnectedKey,multiplexer_.currentWrkElect());
        }

        return status;
    }

    ReturnStatus SystemState::onCommandGetMuxWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if ((multiplexer_.isRunning()) && (multiplexer_.isConnectedWrk()))  
        {
            jsonDat.set(ConnectedKey,multiplexer_.currentWrkElect());
        }
        else
        {
            jsonDat.set(ConnectedKey, false);
        }
        return status;
    }

    ReturnStatus SystemState::onCommandDisconnAllMuxElect(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (multiplexer_.isRunning())
        {
            multiplexer_.disconnectWrkElect();
            multiplexer_.disconnectRefElect();
            multiplexer_.disconnectCtrElect();
        }
        return status;
    }

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ConnectedKey + String("' to bool");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            electrodeSwitch_.setRefConnected(true);
        }
        else
        {
            electrodeSwitch_.setRefConnected(false);
        }

        jsonDat.set(ConnectedKey, electrodeSwitch_.refConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(ConnectedKey, electrodeSwitch_.refConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ConnectedKey + String("' to bool");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            electrodeSwitch_.setCtrConnected(true);
        }
        else
        {
            electrodeSwitch_.setCtrConnected(false);
        }

        jsonDat.set(ConnectedKey, electrodeSwitch_.ctrConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(ConnectedKey, electrodeSwitch_.ctrConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ConnectedKey + String("' to bool");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            electrodeSwitch_.setWrkConnected(true);
        }
        else
        {
            electrodeSwitch_.setWrkConnected(false);
        }

        jsonDat.set(ConnectedKey, electrodeSwitch_.wrkConnected());
        return status;
    }
#endif


#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(ConnectedKey, electrodeSwitch_.wrkConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetAllElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ConnectedKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ConnectedKey;
            return status;
        }

        if ( !(jsonMsg[ConnectedKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ConnectedKey + String("' to bool");
            return status;
        }

        if (jsonMsg.get<bool>(ConnectedKey))
        {
            electrodeSwitch_.setAllConnected(true);
        }
        else
        {
            electrodeSwitch_.setAllConnected(false);
        }

        jsonDat.set(ConnectedKey, electrodeSwitch_.allConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetAllElectConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(ConnectedKey, electrodeSwitch_.allConnected());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetElectAutoConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(ElectAutoConnectKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + ElectAutoConnectKey;
            return status;
        }

        if ( !(jsonMsg[ElectAutoConnectKey].is<bool>()) )
        {
            status.success = false;
            status.message = String("unable to convert '") + ElectAutoConnectKey + String("' to bool");
            return status;
        }

        if (jsonMsg.get<bool>(ElectAutoConnectKey))
        {
            electrodeAutoConnect_ = true;
        }
        else
        { 
            electrodeAutoConnect_ = false;
        }

        jsonDat.set(ElectAutoConnectKey, electrodeAutoConnect_);
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetElectAutoConn(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(ElectAutoConnectKey, electrodeAutoConnect_);
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandSetRefElectVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(VoltRangeKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + VoltRangeKey;
        }
        else
        {
            String voltRangeName = String((const char *)(jsonMsg[VoltRangeKey]));
            status = analogSubsystem_.setRefElectVoltRangeByName(voltRangeName);
            jsonDat.set(VoltRangeKey,analogSubsystem_.getRefElectVoltRangeName());
        }
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetRefElectVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        jsonDat.set(VoltRangeKey,analogSubsystem_.getRefElectVoltRangeName());
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus SystemState::onCommandGetHardwareVersion(JsonObject &jsonMsg, JsonObject &jsonDat) 
    {
        ReturnStatus status;
        jsonDat.set(VersionKey,HardwareVersion);
        return status;
    }
#endif

    // ------------------------------------------------------------------------------------------


    void SystemState::updateMessageData()
    {
        messageReceiver_.readData();
    }


    void SystemState::processMessages()
    {

        if (messageReceiver_.available())
        {
            ReturnStatus status;
            StaticJsonBuffer<JsonMessageBufferSize> messageJsonBuffer;
            StaticJsonBuffer<JsonMessageBufferSize> commandRespJsonBuffer;

            String message = messageReceiver_.next();
            JsonObject &jsonMsg = messageParser_.parse(message,messageJsonBuffer);

            JsonObject &jsonDat = commandRespJsonBuffer.createObject();
            if (jsonMsg.success())
            {
                status = commandTable_.apply(CommandKey,jsonMsg,jsonDat);
            }
            else
            {
                status.success = false;
                status.message = "unable to parse json";
            }
            messageSender_.sendCommandResponse(status,jsonDat);
        }
    }


    void SystemState::serviceDataBuffer()
    {
        // Check for last sample flag to see if done
        bool run_complete = false;
        if (lastSampleFlag_)
        {
            run_complete = true;
        }

        // Empty data buffer
        size_t buffer_size;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            buffer_size = dataBuffer_.size();
        }

        while (buffer_size > 0)
        {
            Sample sample;
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
            {
                sample = dataBuffer_.front();
                dataBuffer_.pop_front();
                buffer_size = dataBuffer_.size();
            }
            messageSender_.sendSample(sample);
        }

        // Send indication that the run is complete 
        if (run_complete)
        {
            messageSender_.sendSampleEnd();
            lastSampleFlag_ = false;
        }
    }


    void SystemState::setTestTimerCallback(void(*callback)())
    {
        testTimerCallback_ = callback;
    }


    void SystemState::updateTestOnTimer()
    {
        bool done = false;

        if (test_ == nullptr)
        {
            done = true;
        }
        else
        {
            uint64_t t = uint64_t(TestTimerPeriod)*timerCnt_;
            float volt = test_ -> getValue(t);
            analogSubsystem_.setVolt(volt);
            float curr = analogSubsystem_.getCurr();

            int electNum = 0; // Default value (0 is non mux channel)
            int electInd = 0; // Default value 

            if (multiplexer_.isRunning())
            {
                electNum = multiplexer_.currentWrkElect();
                electInd = multiplexer_.electNumToIndex(electNum);
            }

            currLowPass_[electInd].update(curr,lowPassDtSec_);

            if (timerCnt_ > 0)
            {
                if (test_ -> getSampleMethod() == SampleGeneric)
                {
                    // ------------------------------------------------------------------
                    // Send sample data for tests which use normal sampling 
                    // ------------------------------------------------------------------
                    if (timerCnt_%sampleModulus_ == 0)
                    {
                        Sample sample = {t, volt, currLowPass_[electInd].value(),uint8_t(electNum)};
                        dataBuffer_.push_back(sample);
                        if (multiplexer_.isRunning())
                        {
                            multiplexer_.connectNextEnabledWrkElect();   
                        }
                    }
                }
                else
                {
                    // ------------------------------------------------------------------
                    // Send sample for tests which use custom sampling methods
                    // ------------------------------------------------------------------
                    Sample sampleRaw  = {t, volt, currLowPass_[0].value(),uint8_t(electNum)}; // Raw sample data
                    Sample sampleTest = {0, 0.0, 0.0, uint8_t(electNum)}; // Custom sample data (set in updateSample)
                    if (test_ -> updateSample(sampleRaw, sampleTest))
                    {
                        dataBuffer_.push_back(sampleTest);
                        if (multiplexer_.isRunning())
                        {
                            multiplexer_.connectNextEnabledWrkElect();   
                        }
                    }
                }
            }
            done = test_ -> isDone(t);
            timerCnt_++;
        }

        if (done) 
        {
            stopTest();
        }
    }


    void SystemState::startTest()
    {
        if (test_ != nullptr)
        {

#if defined HARDWARE_VERSION_0P2 
            if (electrodeAutoConnect_)
            {
                electrodeSwitch_.setAllConnected(true);
            }
#endif

            timerCnt_ = 0;
            analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());

#if defined HARDWARE_VERSION_0P2 
            analogSubsystem_.autoRefElectVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());
#endif
            test_ -> reset();
            if (multiplexer_.isRunning())
            {
                for (int i=0; i<NumMuxChan; i++)
                {
                    currLowPass_[i].reset();
                }
                lowPassDtSec_ = (1.0e-6*TestTimerPeriod)*float(multiplexer_.numEnabledWrkElect());    
            }
            else
            {
                currLowPass_[0].reset();
                lowPassDtSec_ = 1.0e-6*TestTimerPeriod;    
            }

            testInProgress_ = true;
            testTimer_.begin(testTimerCallback_, TestTimerPeriod);
        }
    }


    void SystemState::stopTest()
    {
        testTimer_.end();
        testInProgress_ = false;
        lastSampleFlag_ = true;
        analogSubsystem_.setVolt(0.0);

#if defined HARDWARE_VERSION_0P2 
        if (electrodeAutoConnect_)
        {
            electrodeSwitch_.setAllConnected(false);
        }
#endif

        if (multiplexer_.isRunning())
        {
            multiplexer_.disconnectWrkElect();
            multiplexer_.disconnectRefElect();
            multiplexer_.disconnectCtrElect();
        }
    }


    void SystemState::setSamplePeriod(uint32_t samplePeriod)
    {
        samplePeriod_ = constrain(samplePeriod, MinimumSamplePeriod, MaximumSamplePeriod);
        updateSampleModulus();
        voltammetry_.setSamplePeriod(uint64_t(samplePeriod_));
    }


    uint32_t SystemState::getSamplePeriod()
    {
        return samplePeriod_;
    }


    void SystemState::updateSampleModulus()
    {
        sampleModulus_ = samplePeriod_/TestTimerPeriod;
    }

}

