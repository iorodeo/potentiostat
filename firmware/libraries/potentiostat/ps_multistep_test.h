#ifndef PS_MULTISTEP_TEST_H
#define PS_MULTISTEP_TEST_H
#include "ps_base_test.h"
#include "ps_constants.h"
#include "ps_time_utils.h"
#include "third-party/Array/Array.h"
#include "third-party/ArduinoJson/ArduinoJson.h"

namespace ps
{

    template<size_t MAX_SIZE>
    class MultiStepTest : public BaseTest
    {

        public:

            //static const String StepArrayKey;

            MultiStepTest(size_t numStep=5);

            virtual void setStepValue(size_t n, float value);
            virtual float getStepValue(size_t n) const;

            virtual void setStepDuration(size_t n, uint64_t duration);
            virtual uint64_t getStepDuration(size_t n) const;
            virtual uint64_t getDuration() const;

            virtual void setNumStep(size_t numStep);
            virtual size_t getNumStep() const;
            virtual size_t getMaxNumStep() const;

            virtual bool isDone(uint64_t t) const override; 
            virtual uint64_t getDoneTime() const override;
            virtual void reset() override; 

            virtual float getValue(uint64_t t) const override; 
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 

            virtual void getParam(JsonObject &jsonDat) override;
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat) override;

        protected:

            Array<float, MAX_SIZE> valueArray_;
            Array<uint64_t, MAX_SIZE> durationArray_;
            size_t numStep_; 

            void setValueAndDurationFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);

    };


    //template<size_t MAX_SIZE>
    //const String MultiStepTest<MAX_SIZE>::StepArrayKey = String("step");


    template<size_t MAX_SIZE>
    MultiStepTest<MAX_SIZE>::MultiStepTest(size_t numStep) 
    { 
        valueArray_.fill(0.0);
        durationArray_.fill(0);
        setNumStep(numStep);
        setName("multiStep");
        setMuxCompatible(true);
    }


    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::setStepValue(size_t n, float value)
    {
        if (n < numStep_)
        {
            valueArray_[n] = value;
        }
    }


    template<size_t MAX_SIZE>
    float MultiStepTest<MAX_SIZE>::getStepValue(size_t n) const
    {
        float value = 0.0;
        if (n < numStep_)
        {
            value = valueArray_[n];
        }
        return value;
    }


    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::setStepDuration(size_t n, uint64_t duration)
    {
        if (n < numStep_)
        {
            durationArray_[n] = duration;
        }
    }
    
    
    template<size_t MAX_SIZE>
    uint64_t MultiStepTest<MAX_SIZE>::getStepDuration(size_t n) const
    {
        uint64_t duration = 0;
        if (n < numStep_)
        {
            duration = durationArray_[n];
        }
        return duration;
    }


    template<size_t MAX_SIZE>
    uint64_t MultiStepTest<MAX_SIZE>::getDuration() const
    {
        uint64_t duration = 0;
        for (size_t i = 0; i<numStep_; i++)
        {
            duration += durationArray_[i];
        }
        return duration;
    }
    
    
    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::setNumStep(size_t size)
    {
        if (size <= MAX_SIZE)
        {
            numStep_ = size;
        }

        valueArray_.clear();
        durationArray_.clear();

        // Set default values
        bool pos = true;
        for (size_t i=0; i< numStep_; i++)
        {
            if (pos)
            {
                valueArray_.push_back(0.5);
                pos = false;
            }
            else
            {
                valueArray_.push_back(-0.5);
                pos = true;
            }
            durationArray_.push_back(1000000);
        }
    }
    
    
    template<size_t MAX_SIZE>
    size_t MultiStepTest<MAX_SIZE>::getNumStep() const
    {
        return numStep_;
    }


    template<size_t MAX_SIZE>
    size_t MultiStepTest<MAX_SIZE>::getMaxNumStep() const
    {
        return MAX_SIZE;
    }
    
    
    template<size_t MAX_SIZE>
    bool MultiStepTest<MAX_SIZE>::isDone(uint64_t t) const 
    {
        if (t >= (getDuration() + quietTime_))
        {
            return true;
        }
        else
        {
            return false;
        }

    }


    template<size_t MAX_SIZE>
    uint64_t MultiStepTest<MAX_SIZE>::getDoneTime() const 
    {
        return getDuration() + quietTime_;
    }
    
    
    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::reset() 
    { }
    
    
    template<size_t MAX_SIZE>
    float MultiStepTest<MAX_SIZE>::getValue(uint64_t t) const 
    {
        float value = 0.0;

        if (t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            uint64_t stepEndTime = quietTime_;
            for (size_t i=0; i<numStep_; i++)
            {
                stepEndTime += durationArray_[i];
                if (t <= stepEndTime)
                {
                    value = valueArray_[i];
                    break;
                }
            }
        }
        return value;
    }
    
    
    template<size_t MAX_SIZE>
    float MultiStepTest<MAX_SIZE>::getMaxValue() const 
    {
        float maxValue = 0.0;
        for (size_t i=0; i<numStep_; i++)
        {
            if (i==0)
            {
                maxValue = valueArray_[i];
            }
            else
            {
                maxValue = max(maxValue,valueArray_[i]);
            }
        }
        return maxValue;
    }
    
    
    template<size_t MAX_SIZE>
    float MultiStepTest<MAX_SIZE>::getMinValue() const 
    {
        float minValue = 0.0;
        for (size_t i=0; i<numStep_; i++)
        {
            if (i==0)
            {
                minValue = valueArray_[i];
            }
            else
            {
                minValue = min(minValue,valueArray_[i]);
            }
        }
        return minValue;
    }


    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            JsonArray &jsonStepArray = jsonDatPrm.createNestedArray(StepArrayKey);
            for (size_t i=0; i<numStep_; i++)
            {
                JsonArray &jsonStep = jsonStepArray.createNestedArray();
                jsonStep.add(convertUsToMs(durationArray_[i]));
                jsonStep.add(valueArray_[i]);
            }
        }
    }


    template<size_t MAX_SIZE>
    ReturnStatus MultiStepTest<MAX_SIZE>::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setValueAndDurationFromJson(jsonMsgPrm,jsonDatPrm,status);

        return status;
    }


    // Protected methods
    // --------------------------------------------------------------------------------------------

    template<size_t MAX_SIZE>
    void MultiStepTest<MAX_SIZE>::setValueAndDurationFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (!jsonMsgPrm.containsKey(StepArrayKey))
        {
            status.success = false;
            String errorMsg = StepArrayKey + String(" key not found");
            status.appendToMessage(errorMsg);
            return;
        }

        if (!jsonMsgPrm[StepArrayKey].is<JsonArray&>())
        {
            status.success = false;
            String errorMsg = StepArrayKey + String(" not a JsonArray");
            status.appendToMessage(errorMsg);
            return;
        }

        JsonArray &jsonStepArray = jsonMsgPrm[StepArrayKey];

        if (jsonStepArray.size() > MAX_SIZE)
        {
            status.success = false;
            String errorMsg = StepArrayKey + String(" array too large");
            status.appendToMessage(errorMsg);
            return;
        }

        Array<uint64_t, MAX_SIZE> durationArrayTmp;
        Array<float, MAX_SIZE> valueArrayTmp;

        for (size_t i=0; i<jsonStepArray.size(); i++)
        {
            if (jsonStepArray[i].is<JsonArray&>())
            {
                JsonArray &jsonStep = jsonStepArray[i];

                if (jsonStep.size() == 2)
                {
                    if (jsonStep[0].is<unsigned long>())
                    { 
                        durationArrayTmp.push_back(convertMsToUs(jsonStep.get<unsigned long>(0)));
                    }
                    else
                    {
                        status.success = false;
                        String errorMsg = StepArrayKey + String(" item[0] not uint32");
                        status.appendToMessage(errorMsg);
                        break;
                    }

                    if (jsonStep[1].is<float>())
                    {
                        valueArrayTmp.push_back(jsonStep.get<float>(1));
                    }
                    else
                    {
                        status.success = false;
                        String errorMsg = StepArrayKey + String(" item[1] not float");
                        status.appendToMessage(errorMsg);
                        break;
                    }
                }
                else
                {
                    status.success = false;
                    String errorMsg = StepArrayKey + String(" item size!=2");
                    status.appendToMessage(errorMsg);
                    break;
                }

            }
            else
            {
                status.success = false;
                String errorMsg = StepArrayKey + String(" item not JsonArary");
                status.appendToMessage(errorMsg);
                break;
            }

        } // for (size_t i=0; ... 

        if (status.success)
        {
            setNumStep(jsonStepArray.size());
            JsonArray &jsonStepDatArray = jsonDatPrm.createNestedArray(StepArrayKey);
            for (size_t i=0; i<getNumStep(); i++)
            {
                setStepDuration(i,durationArrayTmp[i]);
                setStepValue(i,valueArrayTmp[i]);
                JsonArray &jsonStepDat = jsonStepDatArray.createNestedArray();
                jsonStepDat.add(convertUsToMs(durationArray_[i]));
                jsonStepDat.add(valueArray_[i]);
            }
        }

    }


} // namespace ps

#endif
