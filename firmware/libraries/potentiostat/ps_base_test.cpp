#include "ps_base_test.h"
#include "ps_constants.h"
#include "ps_time_utils.h"

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


    uint64_t BaseTest::getDoneTime() const
    {
        return quietTime_;
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


    void BaseTest::setQuietValue(float quietValue)
    {
        quietValue_ = quietValue;
    }


    void BaseTest::setQuietValueToStart()
    {
        quietValue_ = getValue(quietTime_);
    }


    float BaseTest::getQuietValue() const
    {
        return quietValue_;
    }

    void BaseTest::setSamplePeriod(uint64_t samplePeriod)
    {
        samplePeriod_ = samplePeriod;
        sampleModulus_ = samplePeriod_/TestTimerPeriod;
    }


    uint64_t BaseTest::getSamplePeriod() const
    {
        return samplePeriod_;
    }


    void BaseTest::setName(String name)
    {
        name_ = name;
    }

    
    String BaseTest::getName()
    {
        return name_;
    }


    void BaseTest::setSampleMethod(SampleMethod sampleMethod) 
    {
        sampleMethod_ = sampleMethod;
    }


    SampleMethod BaseTest::getSampleMethod() const
    {
        return sampleMethod_;
    }


    bool BaseTest::updateSample(Sample sampleRaw, Sample &sampleTest)
    {
        // Only for tests with custom sampling 
        return false;
    }


    void BaseTest::getParam(JsonObject &jsonDat)
    {
        JsonObject &jsonDatPrm = jsonDat.createNestedObject(ParamKey);
        jsonDatPrm.set(QuietValueKey, quietValue_);
        jsonDatPrm.set(QuietTimeKey, convertUsToMs(quietTime_));
    }

    ReturnStatus BaseTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;

        // Extract JsonObject containing parameters
        JsonObject &jsonMsgPrm = getParamJsonObject(jsonMsg,status);
        if (!status.success)
        {
            return status;
        }

        // Set Parameters_ 
        JsonObject &jsonDatPrm = jsonDat.createNestedObject(ParamKey);

        setQuietValueFromJson(jsonMsgPrm, jsonDatPrm, status);
        setQuietTimeFromJson(jsonMsgPrm, jsonDatPrm, status);

        return status;
    }

    bool BaseTest::isMuxCompatible()
    {
        return muxCompatible_;
    }

    void BaseTest::setMuxCompatible(bool value)
    {
        muxCompatible_ = value;
    }

    // Protected Methods
    // ----------------------------------------------------------------------------------

    JsonObject &BaseTest::getParamJsonObject(JsonObject &json, ReturnStatus &status)
    {
        // Extract JsonObject containing parameters
        if (!json.containsKey(ParamKey))
        {
            status.success = false;
            String errorMsg = String("key ") + ParamKey + String(" missing");
            status.appendToMessage(errorMsg);
            return json;
        }
        if (!json[ParamKey].is<JsonObject>())
        {
            status.success = false;
            String errorMsg = ParamKey + String(" not JsonObject");
            status.appendToMessage(errorMsg);
            return json;
        }
        return json[ParamKey];
    }

    void BaseTest::setQuietValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(QuietValueKey))
        {
            if (jsonMsgPrm[QuietValueKey].is<float>())
            {
                setQuietValue(jsonMsgPrm.get<float>(QuietValueKey));
                jsonDatPrm.set(QuietValueKey,getQuietValue());
            }
            else if (jsonMsgPrm[QuietValueKey].is<long>())
            {
                setQuietValue(float(jsonMsgPrm.get<long>(QuietValueKey)));
                jsonDatPrm.set(QuietValueKey,getQuietValue());
            }
            else
            {
                status.success = false;
                String errorMsg = QuietValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void BaseTest::setQuietTimeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(QuietTimeKey))
        {
            if (jsonMsgPrm[QuietTimeKey].is<unsigned long>())
            {
                setQuietTime(convertMsToUs(jsonMsgPrm.get<unsigned long>(QuietTimeKey)));
                jsonDatPrm.set(QuietTimeKey,convertUsToMs(getQuietTime()));
            }
            else
            {
                status.success = false;
                String errorMsg = QuietTimeKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }



} // namespace ps
