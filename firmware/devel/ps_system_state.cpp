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


    void SystemState::setTestTimerCallback(void(*callback)())
    {
        testTimerCallback_ = callback;
    }


    void SystemState::updateTestOnTimer()
    {
        float volt = test_ -> getValue(t_);
        analogSubsystem_.setVolt(volt);
        float curr = analogSubsystem_.getCurr();

        // Don't push every data point
        //Sample sample = {t_, volt, curr};
        //dataBuffer_.push_back(sample);

        if (test_ -> isDone(t_))
        {
            testTimer_.end();
        }
        t_ += dt_;
    }


    void SystemState::startTestTimer()
    {
        t_ = 0.0;
        testTimer_.begin(testTimerCallback_,TestTimerPeriod);
    }


}

