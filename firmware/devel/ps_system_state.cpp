#include "ps_system_state.h"


namespace ps
{

    SystemState::SystemState()
    { 
        testInProgress_ = false;
        timerCnt_ = 0;
        test_ = nullptr;

        currLowPass_.setParam(CurrLowPassParam);
        updateSampleModulus();

        commandTable_.setClient(this);

        commandTable_.registerMethod("cmd","runTest", &SystemState::onCommandRunTest);
        commandTable_.registerMethod("cmd","stopTest", &SystemState::onCommandStopTest);

        commandTable_.registerMethod("cmd","setVolt", &SystemState::onCommandSetVolt);
        commandTable_.registerMethod("cmd","getCurr", &SystemState::onCommandGetCurr);

        commandTable_.registerMethod("cmd","setParam", &SystemState::onCommandSetTestParam);
        commandTable_.registerMethod("cmd","getParam", &SystemState::onCommandGetTestParam);

        commandTable_.registerMethod("cmd","setVoltRange", &SystemState::onCommandSetVoltRange);
        commandTable_.registerMethod("cmd","getVoltRange", &SystemState::onCommandGetVoltRange);

        commandTable_.registerMethod("cmd","setCurrRange", &SystemState::onCommandSetCurrRange);
        commandTable_.registerMethod("cmd","getCurrRange", &SystemState::onCommandGetCurrRange);
    }


    void SystemState::initialize()
    {
        analogSubsystem_.initialize();
        analogSubsystem_.setVolt(0.0);
        messageReceiver_.reset();
    }


    ReturnStatus SystemState::onCommandRunTest(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        test_ = voltammetry_.getTest(jsonRoot);

        if (test_ != nullptr)
        {
            startTest();
        }
        else
        {
            status.success = false;
            status.message = "test not found";
        }
        return status;
    }


    ReturnStatus SystemState::onCommandStopTest(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        stopTest();
        return status;
    }


    ReturnStatus SystemState::onCommandSetVolt(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        if (jsonRoot.containsKey("value"))
        {
            float value = jsonRoot.get<float>("value");
            analogSubsystem_.setVolt(value);
        }
        else
        {
            status.success = false;
            status.message = "no value in json object";
        }
        return status;
    }

    
    ReturnStatus SystemState::onCommandGetCurr(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandSetTestParam(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandGetTestParam(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandSetVoltRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandGetVoltRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandSetCurrRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::onCommandGetCurrRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
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
            String message = messageReceiver_.next();
            JsonObject &jsonRoot = messageParser_.parse(message);

            ReturnStatus status;
            if (jsonRoot.success())
            {
                status = commandTable_.apply("cmd",jsonRoot);
            }
            else
            {
                status.success = false;
                status.message = "unable to parse json";
            }

            messageSender_.sendCommandResponse(status);
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
        analogSubsystem_.setVolt(0.0);
    }

    void SystemState::updateSampleModulus()
    {
        sampleModulus_ = samplePeriod_/TestTimerPeriod;
    }

}


//voltammetry_.cyclicTest.setPeriod(2000000);
//voltammetry_.cyclicTest.setAmplitude(0.8);
//voltammetry_.cyclicTest.setOffset(0.0);
//voltammetry_.cyclicTest.setShift(0.25);
//voltammetry_.cyclicTest.setNumCycles(10);
//voltammetry_.cyclicTest.setQuietTime(3000000);
//voltammetry_.cyclicTest.setQuietValueToStart(); 
//test_ = &voltammetry_.cyclicTest;

//voltammetry_.sinusoidTest.setPeriod(1000000);
//voltammetry_.sinusoidTest.setAmplitude(0.8);
//voltammetry_.sinusoidTest.setOffset(0.0);
//voltammetry_.sinusoidTest.setShift(0.25);
//voltammetry_.sinusoidTest.setNumCycles(10);
//voltammetry_.sinusoidTest.setQuietTime(3000000);
//voltammetry_.sinusoidTest.setQuietValueToStart();
//test_ = &voltammetry_.sinusoidTest;

//voltammetry_.constantTest.setDuration(10000000);
//voltammetry_.constantTest.setValue(1.0);
//voltammetry_.constantTest.setQuietTime(3000000);
//voltammetry_.constantTest.setQuietValue(0.5);
//test_ = &voltammetry_.constantTest;

//voltammetry_.multiStepTest.setNumStep(3);
//voltammetry_.multiStepTest.setStepValue(0,1.0);
//voltammetry_.multiStepTest.setStepValue(1,1.5);
//voltammetry_.multiStepTest.setStepValue(2,2.0);
//voltammetry_.multiStepTest.setStepDuration(0, 1000000);
//voltammetry_.multiStepTest.setStepDuration(1, 2000000);
//voltammetry_.multiStepTest.setStepDuration(2, 3000000);
//voltammetry_.multiStepTest.setQuietTime(5000000);
//voltammetry_.multiStepTest.setQuietValue(0.0);
//test_ = &voltammetry_.multiStepTest;

//voltammetry_.chronoampTest.setStepValue(0,-1.0);
//voltammetry_.chronoampTest.setStepDuration(0,2000000);
//voltammetry_.chronoampTest.setStepValue(1,1.0);
//voltammetry_.chronoampTest.setStepDuration(1,4000000);
//voltammetry_.chronoampTest.setQuietTime(5000000);
//voltammetry_.chronoampTest.setQuietValue(0.0);
//test_ = &voltammetry_.chronoampTest; 
  
//voltammetry_.linearSweepTest.setStartValue(1.2);
//voltammetry_.linearSweepTest.setFinalValue(-1.8);
//voltammetry_.linearSweepTest.setDuration(7000000);
//voltammetry_.linearSweepTest.setQuietTime(5000000);
//voltammetry_.linearSweepTest.setQuietValueToStart();
//test_ = &voltammetry_.linearSweepTest;

//analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());
//analogSubsystem_.setCurrRange(CurrRange10uA);
