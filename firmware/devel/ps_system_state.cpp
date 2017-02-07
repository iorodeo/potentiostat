#include "ps_system_state.h"


namespace ps
{

    SystemState::SystemState()
    { 
        timerCnt_ = 0;
        test_ = nullptr;
        currLowPass_.setParam(CurrLowPassParam);
        updateSampleModulus();

        commandTable_.setClient(this);

        commandTable_.registerMethod("cmd","runTest", &SystemState::runTest);
        commandTable_.registerMethod("cmd","stopTest", &SystemState::stopTest);

        commandTable_.registerMethod("cmd","setVolt", &SystemState::setVolt);
        commandTable_.registerMethod("cmd","getCurr", &SystemState::getCurr);

        commandTable_.registerMethod("cmd","setParam", &SystemState::setTestParam);
        commandTable_.registerMethod("cmd","getParam", &SystemState::getTestParam);

        commandTable_.registerMethod("cmd","setVoltRange", &SystemState::setVoltRange);
        commandTable_.registerMethod("cmd","getVoltRange", &SystemState::getVoltRange);

        commandTable_.registerMethod("cmd","setCurrRange", &SystemState::setCurrRange);
        commandTable_.registerMethod("cmd","getCurrRange", &SystemState::getCurrRange);

    }


    void SystemState::initialize()
    {
        analogSubsystem_.initialize();
        analogSubsystem_.setVolt(0.0);
        messageReceiver_.reset();
    }


    ReturnStatus SystemState::runTest(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        test_ = voltammetry_.getTest(jsonRoot);

        if (test_ != nullptr)
        {
            startTestTimer();
        }
        else
        {
            status.success = false;
            status.message = "test not found";
        }
        return status;
    }


    ReturnStatus SystemState::stopTest(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::setVolt(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }

    
    ReturnStatus SystemState::getCurr(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::setTestParam(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::getTestParam(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::setVoltRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::getVoltRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::setCurrRange(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        Serial.println(__PRETTY_FUNCTION__);
        return status;
    }


    ReturnStatus SystemState::getCurrRange(JsonObject &jsonRoot)
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

            // DEBUG
            //////////////////////////////////////////////////////
            //Serial.print("new msg = ");
            //Serial.println(message);
            /////////////////////////////////////////////////////

            JsonObject &jsonRoot = messageParser_.parse(message);
            String response("");

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

            ///////////////////////////////////////////////////
            // Send comand response.
            // Serial.println(response);
            ///////////////////////////////////////////////////
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
        //float value;
        //uint64_t duration;
        //for (int i=0; i<3; i++)
        //{
        //    duration = voltammetry_.multiStepTest.getStepDuration(i);
        //    Serial.print(i);
        //    Serial.print(" ");
        //    Serial.println(uint32_t(duration));
        //}
        //Serial.println("***");
        //for (int i=0; i<3; i++)
        //{
        //    value = voltammetry_.multiStepTest.getStepValue(i);
        //    Serial.print(i);
        //    Serial.print(" ");
        //    Serial.println(value);
        //}
        //Serial.println("***");
        //for (uint32_t i=0; i<5000000; i=i+100000)
        //{
        //    Serial.print(i);
        //    Serial.print(" ");
        //    value = voltammetry_.multiStepTest.getValue(i);
        //    Serial.println(value);
        //    Serial.println();
        //}
    }


    void SystemState::setTestTimerCallback(void(*callback)())
    {
        testTimerCallback_ = callback;
    }


    void SystemState::updateTestOnTimer()
    {
        if (test_ != nullptr)
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

            if (test_ -> isDone(t))
            {
                testTimer_.end();
                analogSubsystem_.setVolt(0.0);
            }

            timerCnt_++;
        }
        else
        {
            /////////////////////////////////////////
            // TODO:  stop test.
            /////////////////////////////////////////
            return;
        }
    }


    void SystemState::startTestTimer()
    {
        if (test_ != nullptr)
        {
            timerCnt_ = 0;
            analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());

            test_ -> reset();
            currLowPass_.reset();

            testTimer_.begin(testTimerCallback_, TestTimerPeriod);
        }
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
