#include "ps_voltammetry.h"

namespace ps
{

    Voltammetry::Voltammetry()
    {
        chronoampTest.setNumStep(2);
        chronoampTest.setName("chronoamp");

        availableTests_.push_back(&cyclicTest);
        availableTests_.push_back(&sinusoidTest);
        availableTests_.push_back(&constantTest);
        availableTests_.push_back(&linearSweepTest);
        availableTests_.push_back(&chronoampTest);
        availableTests_.push_back(&multiStepTest);
    }
            

    BaseTest *Voltammetry::getTest(String name)
    {
        BaseTest *testPtr = nullptr;
        for (size_t i=0; i<availableTests_.size(); i++)
        {
            String currName = (availableTests_[i] -> getName()).trim();
            if (name.equals(currName))
            {
                testPtr = availableTests_[i];
                break;
            }
        }
        return testPtr;
    }


    BaseTest *Voltammetry::getTest(JsonObject &json)
    {
        BaseTest *testPtr = nullptr;
        String testKey = String("test");
        if (json.containsKey(testKey.c_str()))
        {
            String testName = String((const char *)(json[testKey.c_str()]));
            testPtr = getTest(testName);
        }
        return testPtr;
    }

} // namespace ps
