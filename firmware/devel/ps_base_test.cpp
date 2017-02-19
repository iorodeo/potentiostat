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

        // Get quietValue_ 
        if (jsonPrm.containsKey(QuietValueKey))
        {
            if (jsonPrm[QuietValueKey].is<float>())
            {
                quietValue_  = jsonPrm.get<float>(QuietValueKey);
                jsonDat.set(QuietValueKey,quietValue_,JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = QuietValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }

        // Set quietTime_
        if (jsonPrm.containsKey(QuietTimeKey))
        {
            if (jsonPrm[QuietTimeKey].is<unsigned long>())
            {
                quietTime_ = convertMsToUs(jsonPrm.get<unsigned long>(QuietTimeKey));
                jsonDat.set(QuietTimeKey,convertUsToMs(quietTime_));
            }
            else
            {
                status.success = false;
                String errorMsg = QuietTimeKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }

        return status;
    }

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

} // namespace ps
