#include "ps_constant_test.h"

namespace ps
{
    ConstantTest::ConstantTest()
    {} 


    void ConstantTest::setDuration(uint64_t duration)
    {
        duration_ = duration;
    }


    uint64_t ConstantTest::getDuration() const
    {
        return duration_;
    }


    void ConstantTest::setValue(float value)
    {
        value_ = value;
    }


    float ConstantTest::getValue(uint64_t t) const 
    {
        return value_;
    }


    bool ConstantTest::isDone(uint64_t t) const 
    {
        return (t >= duration_ );
    }


    float ConstantTest::getMaxValue() const 
    {
        return value_;
    }


    float ConstantTest::getMinValue() const 
    {
        return value_;
    }


} // namespace ps
