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

        currLowPass_.setParam(CurrLowPassParam);
        setSamplePeriod(DefaultSamplePeriod);
    }


    void SystemState::initialize()
    {
        commandTable_.setClient(this);
        commandTable_.registerMethod(CommandKey,   RunTestCmd,          &SystemState::onCommandRunTest);
        commandTable_.registerMethod(CommandKey,   StopTestCmd,         &SystemState::onCommandStopTest);
        commandTable_.registerMethod(CommandKey,   GetVoltCmd,          &SystemState::onCommandGetVolt);
        commandTable_.registerMethod(CommandKey,   SetVoltCmd,          &SystemState::onCommandSetVolt);
        commandTable_.registerMethod(CommandKey,   GetCurrCmd,          &SystemState::onCommandGetCurr);
        commandTable_.registerMethod(CommandKey,   GetRefVoltCmd,       &SystemState::onCommandGetRefVolt);
        commandTable_.registerMethod(CommandKey,   SetParamCmd,         &SystemState::onCommandSetTestParam);
        commandTable_.registerMethod(CommandKey,   GetParamCmd,         &SystemState::onCommandGetTestParam);
        commandTable_.registerMethod(CommandKey,   SetVoltRangeCmd,     &SystemState::onCommandSetVoltRange);
        commandTable_.registerMethod(CommandKey,   GetVoltRangeCmd,     &SystemState::onCommandGetVoltRange);
        commandTable_.registerMethod(CommandKey,   SetCurrRangeCmd,     &SystemState::onCommandSetCurrRange);
        commandTable_.registerMethod(CommandKey,   GetCurrRangeCmd,     &SystemState::onCommandGetCurrRange);
        commandTable_.registerMethod(CommandKey,   SetDeviceIdCmd,      &SystemState::onCommandSetDeviceId);
        commandTable_.registerMethod(CommandKey,   GetDeviceIdCmd,      &SystemState::onCommandGetDeviceId);
        commandTable_.registerMethod(CommandKey,   SetSamplePeriodCmd,  &SystemState::onCommandSetSamplePeriod);
        commandTable_.registerMethod(CommandKey,   GetSamplePeriodCmd,  &SystemState::onCommandGetSamplePeriod);
        commandTable_.registerMethod(CommandKey,   GetTestDoneTimeCmd,  &SystemState::onCommandGetTestDoneTime);
        commandTable_.registerMethod(CommandKey,   GetTestNamesCmd,     &SystemState::onCommandGetTestNames);
        commandTable_.registerMethod(CommandKey,   GetVersionCmd,       &SystemState::onCommandGetVersion);
        commandTable_.registerMethod(CommandKey,   GetVariantCmd,       &SystemState::onCommandGetVariant);

        analogSubsystem_.initialize();
        analogSubsystem_.setVolt(0.0);
        messageReceiver_.reset();
    }


    ReturnStatus SystemState::onCommandRunTest(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = voltammetry_.getTest(jsonMsg,jsonDat,test_);

        if ((status.success) && (test_ != nullptr))
        {
            startTest();
        }
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
        jsonDat.set(VoltKey,volt,JsonFloatDecimals);
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
        jsonDat.set(VoltKey,volt,JsonFloatDecimals);
        return status;
    }

    
    ReturnStatus SystemState::onCommandGetCurr(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        float curr = analogSubsystem_.getCurr();
        jsonDat.set(CurrKey,curr,JsonFloatDecimals);
        return status;
    }


    ReturnStatus SystemState::onCommandGetRefVolt(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        float refVolt = analogSubsystem_.getRefElectVolt();
        jsonDat.set(RefVoltKey,refVolt,JsonFloatDecimals);
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


    void SystemState::updateMessageData()
    {
        messageReceiver_.readData();
    }


    void SystemState::processMessages()
    {
        if (messageReceiver_.available())
        {
            ReturnStatus status;

            String message = messageReceiver_.next();
            JsonObject &jsonMsg = messageParser_.parse(message);

            // ArduinoJson upgrade
            // ----------------------------------------------
            //commandRespJsonBuffer_.clear();
            // ----------------------------------------------
            commandRespJsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>();
            JsonObject &jsonDat = commandRespJsonBuffer_.createObject();
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
            currLowPass_.update(curr,LowPassDtSec);

            if (timerCnt_ > 0)
            {
                if (test_ -> getSampleMethod() == SampleGeneric)
                {
                    // Send sample data for tests which use generic sampling 
                    if (timerCnt_%sampleModulus_ == 0)
                    {
                        Sample sample = {t, volt, currLowPass_.value()};
                        dataBuffer_.push_back(sample);
                    }
                }
                else
                {
                    // Send sample for tests which use custom sampling methods
                    Sample sampleRaw  = {t, volt, currLowPass_.value()}; // Raw sample data
                    Sample sampleTest = {0, 0.0, 0.0}; // Custom sample data (set in updateSample)
                    if (test_ -> updateSample(sampleRaw, sampleTest))
                    {
                        dataBuffer_.push_back(sampleTest);
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
            timerCnt_ = 0;
            analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());

            test_ -> reset();
            currLowPass_.reset();

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

