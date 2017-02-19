#include "ps_base_test.h"
#include "ps_constants.h"
#include "ps_time_utils.h"

namespace ps
{

    const String BaseTest::ParamKey = String("param");
    const String BaseTest::QuietValueKey = String("quietValue"); 
    const String BaseTest::QuietTimeKey = String("quietTime");

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

    void BaseTest::setName(String name)
    {
        name_ = name;
    }

    
    String BaseTest::getName()
    {
        return name_;
    }


    void BaseTest::getParam(JsonObject &jsonDat)
    {
        jsonDat.set(QuietValueKey, quietValue_, JsonFloatDecimals);
        jsonDat.set(QuietTimeKey, convertUsToMs(quietTime_));
    }

    ReturnStatus BaseTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;

        // Extract JsonObject containing parameters
        JsonObject &jsonPrm = getParamJsonObject(jsonMsg,status);
        if (!status.success)
        {
            return status;
        }

        // Set Parameters_ 
        setQuietValueFromJson(jsonPrm,jsonDat,status);
        setQuietTimeFromJson(jsonPrm,jsonDat,status);

        return status;
    }

    // Protected Methods
    // ----------------------------------------------------------------------------------

    JsonObject &BaseTest::getParamJsonObject(JsonObject &jsonMsg, ReturnStatus &status)
    {
        // Extract JsonObject containing parameters
        if (!jsonMsg.containsKey(ParamKey))
        {
            status.success = false;
            String errorMsg = String("key ") + ParamKey + String(" missing");
            status.appendToMessage(errorMsg);
            return jsonMsg;
        }
        if (!jsonMsg[ParamKey].is<JsonObject>())
        {
            status.success = false;
            String errorMsg = ParamKey + String(" not JsonObject");
            status.appendToMessage(errorMsg);
            return jsonMsg;
        }
        return jsonMsg[ParamKey];
    }

    void BaseTest::setQuietValueFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(QuietValueKey))
        {
            if (jsonPrm[QuietValueKey].is<float>())
            {
                setQuietValue(jsonPrm.get<float>(QuietValueKey));
                jsonDat.set(QuietValueKey,getQuietValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = QuietValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void BaseTest::setQuietTimeFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(QuietTimeKey))
        {
            if (jsonPrm[QuietTimeKey].is<unsigned long>())
            {
                setQuietTime(convertMsToUs(jsonPrm.get<unsigned long>(QuietTimeKey)));
                jsonDat.set(QuietTimeKey,convertUsToMs(getQuietTime()));
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
