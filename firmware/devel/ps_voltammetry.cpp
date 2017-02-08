#include "ps_voltammetry.h"

namespace ps
{

    const String Voltammetry::TestKey("test");

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

    
    ReturnStatus Voltammetry::getTest(JsonObject &jsonMsg, JsonObject &jsonDat, BaseTest* &testPtr)
    {
        ReturnStatus status;
        if (jsonMsg.containsKey(TestKey))
        {
            String testName = String((const char *)(jsonMsg[TestKey]));
            testPtr = getTest(testName);
            jsonDat.set(TestKey,testName);
            if (testPtr == nullptr)
            {
                status.success = false;
                status.message = String("test not found"); 
            }
        }
        else
        {
            status.success = false;
            status.message = String("json does not contain key: ") + TestKey;
        }
        return status;
    }


    ReturnStatus Voltammetry::getParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (jsonMsg.containsKey(TestKey))
        {

        }
        else
        {
            status.success = false;
            status.message = "test not found";
        }

        return status;
    }
    
    
    ReturnStatus Voltammetry::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;

        return status;
    }


} // namespace ps
