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


    void LinearSweepTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);
        jsonDat.set(StartValueKey, startValue_, JsonFloatDecimals);
        jsonDat.set(FinalValueKey, finalValue_, JsonFloatDecimals);
        jsonDat.set(DurationKey, convertUsToMs(duration_));
    }

    ReturnStatus LinearSweepTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = BaseTest::setParam(jsonMsg,jsonDat);

        // Extract JsonObject containing parameters
        JsonObject &jsonPrm = getParamJsonObject(jsonMsg,status);
        if (!status.success)
        {
            return status;
        }

        // Set parameters
        setStartValueFromJson(jsonPrm,jsonDat,status);
        setFinalValueFromJson(jsonPrm,jsonDat,status);
        setDurationFromJson(jsonPrm,jsonDat,status);

        return status;
    }

    // Protected methods
    // ----------------------------------------------------------------------------------

    //float startValue_ = -0.5;
    //float finalValue_ =  0.5;
    //uint64_t duration_ = 2000000;

    void LinearSweepTest::setStartValueFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(StartValueKey))
        {
            if (jsonPrm[StartValueKey].is<float>())
            {
                setStartValue(jsonPrm.get<float>(StartValueKey));
                jsonDat.set(StartValueKey,getStartValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = StartValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void LinearSweepTest::setFinalValueFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(FinalValueKey))
        {
            if (jsonPrm[FinalValueKey].is<float>())
            {
                setFinalValue(jsonPrm.get<float>(FinalValueKey));
                jsonDat.set(FinalValueKey,getFinalValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = FinalValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void LinearSweepTest::setDurationFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(DurationKey))
        {
            if (jsonPrm[DurationKey].is<unsigned long>())
            {
                setDuration(convertMsToUs(jsonPrm.get<unsigned long>(DurationKey)));
                jsonDat.set(DurationKey,convertUsToMs(getDuration()));
            }
            else
            {
                status.success = false;
                String errorMsg = DurationKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }


} // namespace ps
