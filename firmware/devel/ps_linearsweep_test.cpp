#include "ps_linearsweep_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"

namespace ps
{

    LinearSweepTest::LinearSweepTest()
    { 
        setName("linearSweep");
    }


    void LinearSweepTest::setStartValue(float value)
    {
        startValue_ = value;
    }


    float LinearSweepTest::getStartValue() const
    {
        return startValue_;
    }


    void LinearSweepTest::setFinalValue(float value)
    {
        finalValue_ = value;
    }


    float LinearSweepTest::getFinalValue() const
    {
        return finalValue_;
    }


    void LinearSweepTest::setDuration(uint64_t duration)
    {
        duration_ = duration;
    }


    uint64_t LinearSweepTest::getDuration() const
    {
        return duration_;
    }


    bool LinearSweepTest::isDone(uint64_t t) const 
    {
        if (t >= (duration_ + quietTime_))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    float LinearSweepTest::getValue(uint64_t t) const 
    {
        float value = 0.0;
        if (t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            uint64_t s = t - quietTime_;
            value = ((finalValue_ - startValue_)*s)/duration_ + startValue_;
        }
        return value;
    }


    float LinearSweepTest::getMaxValue() const 
    {
        return max(startValue_, max(finalValue_, quietValue_));
    }


    float LinearSweepTest::getMinValue() const 
    {
        return min(startValue_, min(finalValue_, quietValue_));
    }


    void LinearSweepTest::getParam(JsonObject &json)
    {
        BaseTest::getParam(json);
        json.set("startValue", startValue_, JsonFloatDecimals);
        json.set("finalValue", finalValue_, JsonFloatDecimals);
        json.set("duration", convertUsToMs(duration_));
    }

    void LinearSweepTest::setParam(JsonObject &json)
    {
    }

} // namespace ps
