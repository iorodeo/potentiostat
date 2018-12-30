#include "ps_constant_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"

namespace ps
{

    ConstantTest::ConstantTest() 
    { 
        setName("constant");
        setMuxCompatible(true);
    } 


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


    float ConstantTest::getValue()
    {
        return value_;
    }


    float ConstantTest::getValue(uint64_t t) const 
    {
        if (t < quietTime_)
        {
            return quietValue_;
        }
        else
        {
            return value_;
        }
    }


    bool ConstantTest::isDone(uint64_t t) const 
    {
        return (t >= (duration_ + quietTime_));
    }


    uint64_t ConstantTest::getDoneTime() const
    {
        return duration_ + quietTime_;
    }


    float ConstantTest::getMaxValue() const 
    {
        return max(value_,quietValue_);
    }


    float ConstantTest::getMinValue() const 
    {
        return min(value_,quietValue_);
    }


    void ConstantTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            jsonDatPrm.set(ValueKey, value_);
            jsonDatPrm.set(DurationKey, convertUsToMs(duration_));
        }
    }

    ReturnStatus ConstantTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setDurationFromJson(jsonMsgPrm,jsonDatPrm,status);
        setValueFromJson(jsonMsgPrm,jsonDatPrm,status);

        return status;
    }


    // Protected Methods
    // ----------------------------------------------------------------------------------

    void ConstantTest::setDurationFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(ValueKey))
        {
            if (jsonMsgPrm[ValueKey].is<float>())
            {
                setValue(jsonMsgPrm.get<float>(ValueKey));
                jsonDatPrm.set(ValueKey,getValue());
            }
            else if (jsonMsgPrm[ValueKey].is<long>())
            {
                setValue(float(jsonMsgPrm.get<long>(ValueKey)));
                jsonDatPrm.set(ValueKey,getValue());
            }
            else
            {
                status.success = false;
                String errorMsg = ValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void ConstantTest::setValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
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
