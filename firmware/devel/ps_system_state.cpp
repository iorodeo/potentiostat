#include "ps_system_state.h"
#include "ps_device_id_eeprom.h"


namespace ps
{

    SystemState::SystemState()
    { 
        testInProgress_ = false;
        lastSampleFlag_ = false;
        timerCnt_ = 0;
        test_ = nullptr;

        currLowPass_.setParam(CurrLowPassParam);
        updateSampleModulus();
    }


    void SystemState::initialize()
    {
        commandTable_.setClient(this);
        commandTable_.registerMethod(CommandKey,  RunTestCmd,      &SystemState::onCommandRunTest);
        commandTable_.registerMethod(CommandKey,  StopTestCmd,     &SystemState::onCommandStopTest);
        commandTable_.registerMethod(CommandKey,  GetVoltCmd,      &SystemState::onCommandGetVolt);
        commandTable_.registerMethod(CommandKey,  SetVoltCmd,      &SystemState::onCommandSetVolt);
        commandTable_.registerMethod(CommandKey,  GetCurrCmd,      &SystemState::onCommandGetCurr);
        commandTable_.registerMethod(CommandKey,  SetParamCmd,     &SystemState::onCommandSetTestParam);
        commandTable_.registerMethod(CommandKey,  GetParamCmd,     &SystemState::onCommandGetTestParam);
        commandTable_.registerMethod(CommandKey,  SetVoltRangeCmd, &SystemState::onCommandSetVoltRange);
        commandTable_.registerMethod(CommandKey,  GetVoltRangeCmd, &SystemState::onCommandGetVoltRange);
        commandTable_.registerMethod(CommandKey,  SetCurrRangeCmd, &SystemState::onCommandSetCurrRange);
        commandTable_.registerMethod(CommandKey,  GetCurrRangeCmd, &SystemState::onCommandGetCurrRange);
        commandTable_.registerMethod(CommandKey,  SetDeviceIdCmd,  &SystemState::onCommandSetDeviceId);
        commandTable_.registerMethod(CommandKey,  GetDeviceIdCmd,  &SystemState::onCommandGetDeviceId);

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

        if (!jsonMsg[VoltKey].is<float>())
        {
            status.success = false;
            status.message = String("unable to convert volt to float");
            return status;
        }

        float volt = jsonMsg.get<float>(VoltKey);
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
        // Extract data from buffer and send
        while (dataBuffer_.size() > 0)
        {
            Sample sample = dataBuffer_.front();
            dataBuffer_.pop_front();
            messageSender_.sendSample(sample);
        }

        if (lastSampleFlag_)
        {
            messageSender_.sendSampleEnd();
            lastSampleFlag_ = false;
        }
    }


    void SystemState::debug()
    {
        Serial.println(analogSubsystem_.getVoltRangeName());
        Serial.println(analogSubsystem_.getCurrRangeName());
        Serial.println(VoltRangeArray[0].name());
        Serial.println("hello");
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

            if (timerCnt_%sampleModulus_ == 0)
            {
                Sample sample = {t, volt, currLowPass_.value()};
                dataBuffer_.push_back(sample);
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

    void SystemState::updateSampleModulus()
    {
        sampleModulus_ = samplePeriod_/TestTimerPeriod;
    }

}


