#include "ps_system_state.h"


namespace std
{
    // Required for using std::function ...
    void __throw_bad_function_call() { exit(0); }
}

namespace ps
{

    SystemState::SystemState()
    { };


    void SystemState::initialize()
    {
        analogSubsystem_.initialize();
        analogSubsystem_.setVoltRange(VoltRange1V);
        analogSubsystem_.setCurrRange(CurrRange10uA);

        voltammetry_.cyclicTest.setPeriod(1.0);
        voltammetry_.cyclicTest.setAmplitude(0.7);
        voltammetry_.cyclicTest.setOffset(0.0);
        voltammetry_.cyclicTest.setLag(0.0);
        voltammetry_.cyclicTest.setNumCycles(10);

        testGetVolt_ = std::bind(&CyclicTest::getValue, &voltammetry_.cyclicTest, std::placeholders::_1);
        testIsDone_  = std::bind(&CyclicTest::isDone,   &voltammetry_.cyclicTest, std::placeholders::_1);
    }

    void SystemState::setTestTimerCallback(void(*callback)())
    {
        testTimerCallback_ = callback;
    }


    void SystemState::updateTestOnTimer()
    {

        float volt = testGetVolt_(t_);
        analogSubsystem_.setVolt(volt);
        float curr = analogSubsystem_.getCurr();

        // Don't push every data point
        TestData data = {t_, volt, curr};
        //dataBuffer_.push_back(data);

        if (testIsDone_(t_))
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

