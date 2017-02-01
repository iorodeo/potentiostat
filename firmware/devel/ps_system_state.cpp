#include "ps_system_state.h"


namespace ps
{

    SystemState::SystemState()
    { 
        test_ = &voltammetry_.baseTest;
        currLowPass_.setParam(CurrLowPassParam);
    }


    void SystemState::initialize()
    {
        analogSubsystem_.initialize();
        analogSubsystem_.setVolt(0.0);

        //voltammetry_.cyclicTest.setPeriod(2000000);
        //voltammetry_.cyclicTest.setAmplitude(0.8);
        //voltammetry_.cyclicTest.setOffset(0.0);
        //voltammetry_.cyclicTest.setLag(0);
        //voltammetry_.cyclicTest.setNumCycles(10);
        //test_ = &voltammetry_.cyclicTest;

        voltammetry_.sinusoidTest.setPeriod(1000000);
        voltammetry_.sinusoidTest.setAmplitude(0.8);
        voltammetry_.sinusoidTest.setOffset(0.0);
        voltammetry_.sinusoidTest.setLag(0);
        voltammetry_.sinusoidTest.setNumCycles(10);
        test_ = &voltammetry_.sinusoidTest;

        analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());
        analogSubsystem_.setCurrRange(CurrRange10uA);

    }


    void SystemState::serviceDataBuffer()
    {
        Serial.print("BufferSize: ");
        Serial.println(int(dataBuffer_.size()));

        char buf[100];

        while (dataBuffer_.size() > 0)
        {
            Sample sample = dataBuffer_.front();
            dataBuffer_.pop_front();
            Serial.print("t = ");
            snprintf(buf,sizeof(buf),"%llu", sample.t);
            Serial.print(buf);
            Serial.print(", volt = ");
            Serial.println(sample.volt,10);
        }
    }


    void SystemState::setTestTimerCallback(void(*callback)())
    {
        testTimerCallback_ = callback;
    }


    void SystemState::updateTestOnTimer()
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


    void SystemState::startTestTimer()
    {
        timerCnt_ = 0;
        sampleModulus_ = samplePeriod_/TestTimerPeriod;
        currLowPass_.reset();
        test_ -> reset();
        testTimer_.begin(testTimerCallback_, TestTimerPeriod);
    }


}

