#include "ps_linearsweep_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"

namespace ps
{

    LinearSweepTest::LinearSweepTest()
    { 
        setName("linearSweep");
        setMuxCompatible(true);
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

    uint64_t LinearSweepTest::getDoneTime() const
    {
        return duration_ + quietTime_;
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

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            jsonDatPrm.set(StartValueKey, startValue_);
            jsonDatPrm.set(FinalValueKey, finalValue_);
            jsonDatPrm.set(DurationKey, convertUsToMs(duration_));
        }
    }

    ReturnStatus LinearSweepTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = BaseTest::setParam(jsonMsg,jsonDat);

        // Extract parameter JsonObjects
        JsonObject &jsonMsgPrm = getParamJsonObject(jsonMsg,status);
        if (!status.success)
        {
            return status;
        }

        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);
        if (!status.success)
        {
            return status;
        }

        // Set parameters
        setStartValueFromJson(jsonMsgPrm,jsonDatPrm,status);
        setFinalValueFromJson(jsonMsgPrm,jsonDatPrm,status);
        setDurationFromJson(jsonMsgPrm,jsonDatPrm,status);

        return status;
    }

    // Protected methods
    // ----------------------------------------------------------------------------------

    void LinearSweepTest::setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(StartValueKey))
        {
            if (jsonMsgPrm[StartValueKey].is<float>())
            {
                setStartValue(jsonMsgPrm.get<float>(StartValueKey));
                jsonDatPrm.set(StartValueKey,getStartValue());
            }
            else if (jsonMsgPrm[StartValueKey].is<long>())
            {
                setStartValue(float(jsonMsgPrm.get<long>(StartValueKey)));
                jsonDatPrm.set(StartValueKey,getStartValue());
            }
            else
            {
                status.success = false;
                String errorMsg = StartValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void LinearSweepTest::setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(FinalValueKey))
        {
            if (jsonMsgPrm[FinalValueKey].is<float>())
            {
                setFinalValue(jsonMsgPrm.get<float>(FinalValueKey));
                jsonDatPrm.set(FinalValueKey,getFinalValue());
            }
            else if (jsonMsgPrm[FinalValueKey].is<long>())
            {
                setFinalValue(float(jsonMsgPrm.get<long>(FinalValueKey)));
                jsonDatPrm.set(FinalValueKey,getFinalValue());
            }
            else
            {
                status.success = false;
                String errorMsg = FinalValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void LinearSweepTest::setDurationFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(DurationKey))
        {
            if (jsonMsgPrm[DurationKey].is<unsigned long>())
            {
                setDuration(convertMsToUs(jsonMsgPrm.get<unsigned long>(DurationKey)));
                jsonDatPrm.set(DurationKey,convertUsToMs(getDuration()));
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
