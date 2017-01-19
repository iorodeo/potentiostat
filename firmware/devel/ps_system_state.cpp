#include "ps_system_state.h"


namespace ps
{

    SystemState::SystemState()
    { 
        test_ = &voltammetry_.baseTest;
    }


    void SystemState::initialize()
    {
        analogSubsystem_.initialize();

        voltammetry_.cyclicTest.setPeriod(1.0);
        voltammetry_.cyclicTest.setAmplitude(0.7);
        voltammetry_.cyclicTest.setOffset(0.0);
        voltammetry_.cyclicTest.setLag(0.0);
        voltammetry_.cyclicTest.setNumCycles(10);

        test_ = &voltammetry_.cyclicTest;

        analogSubsystem_.autoVoltRange(test_ -> getMinValue(), test_ -> getMaxValue());
        analogSubsystem_.setCurrRange(CurrRange10uA);

    }


    void SystemState::serviceDataBuffer()
    {
        Serial.print("BufferSize: ");
        Serial.println(int(dataBuffer_.size()));

        while (dataBuffer_.size() > 0)
        {
            Sample sample = dataBuffer_.front();
            dataBuffer_.pop_front();
            Serial.print("t = ");
            Serial.print(sample.t,10);
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
        double t = double(timerCnt_)*timerDt_;

        float volt = test_ -> getValue(t);
        analogSubsystem_.setVolt(volt);

        float curr = analogSubsystem_.getCurr();

        if (timerCnt_%sampleModulus_ == 0)
        {
            Sample sample = {t, volt, curr};
            dataBuffer_.push_back(sample);
        }

        if (test_ -> isDone(t))
        {
            testTimer_.end();
        }

        timerCnt_++;
    }


    void SystemState::startTestTimer()
    {
        timerCnt_ = 0;
        sampleModulus_ = samplePeriod_us_/TestTimerPeriod_us;
        testTimer_.begin(testTimerCallback_, TestTimerPeriod_us);
    }


}

