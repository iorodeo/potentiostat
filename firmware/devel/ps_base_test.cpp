#include "ps_base_test.h"

namespace ps
{

    BaseTest::BaseTest() 
    { }


    bool BaseTest::isDone(uint64_t t) const 
    { 
        if (t < quietTime_)
        {
            return false;
        }
        else
        {
            return true;
        }
    }


    void BaseTest::reset() 
    { }


    float BaseTest::getValue(uint64_t t) const 
    { 
        if (t < quietTime_)
        {
            return quietValue_;
        }
        else
        {
            return 0.0;
        }
    }


    float BaseTest::getMaxValue() const 
    { 
        return max(quietValue_,0.0); 
    }


    float BaseTest::getMinValue() const 
    { 
        return min(quietValue_,0.0); 
    }

    void BaseTest::setQuietTime(uint64_t quietTime)
    {
        quietTime_ = quietTime;
    }


    uint64_t BaseTest::getQuietTime() const
    {
        return quietTime_;
    }


    void BaseTest::setQuietValue(float quietVolt)
    {
        quietValue_ = quietVolt;
    }


    void BaseTest::setQuietValueToStart()
    {
        quietValue_ = getValue(quietTime_);
    }

    uint64_t BaseTest::getQuietValue() const
    {
        return quietValue_;
    }

    void BaseTest::setName(String name)
    {
        name_ = name;
    }

    
    String BaseTest::getName()
    {
        return name_;
    }


} // namespace ps
