#include "ps_squarewave_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"
#include <math.h>

namespace ps 
{
    // Public methods
    // --------------------------------------------------------------------------------------------
    SquareWaveTest::SquareWaveTest()
    { 
        setName("squareWave");
        updateDoneTime();
        updateMaxMinValues();
    };

    void SquareWaveTest::setStartValue(float value)
    {
        startValue_ = value;
        updateDoneTime();
        updateMaxMinValues();
    }


    float SquareWaveTest::getStartValue()
    {
        return startValue_;
    }


    void SquareWaveTest::setFinalValue(float value)
    {
        finalValue_ = value;
        updateDoneTime();
        updateMaxMinValues();
    }


    float SquareWaveTest::getFinalValue()
    {
        return finalValue_;
    }


    void SquareWaveTest::setStepValue(float value)
    {
        stepValue_ = value;
        updateDoneTime();
    }


    float SquareWaveTest::getStepValue()
    {
        return stepValue_;
    }


    void SquareWaveTest::setAmplitude(float value)
    {
        amplitude_ = value;
    }


    float SquareWaveTest::getAmplitude()
    {
        return amplitude_;
    }


    float SquareWaveTest::getMaxValue() const 
    {
        float maxValue = max(startValue_, finalValue_) + amplitude_;
        return max(maxValue, quietValue_);
    }


    float SquareWaveTest::getMinValue() const 
    {
        float minValue = min(startValue_, finalValue_) - amplitude_;
        return min(minValue, quietValue_);
    }


    void SquareWaveTest::setSamplePeriod(uint64_t samplePeriod)
    {
        samplePeriod_ = samplePeriod;
        halfSamplePeriod_ = samplePeriod >> 1;
    }

    bool SquareWaveTest::isDone(uint64_t t) const 
    {
        if (t >= doneTime_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    uint64_t SquareWaveTest::getDoneTime() const
    {
        return doneTime_;

    }


    float SquareWaveTest::getValue(uint64_t t) const 
    {
        float value = 0.0;
        if ( t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            // Get test time, staircase step count, and
            // fraction of current test completed.
            uint64_t tTest = t - quietTime_;
            uint64_t stepCount = tTest/samplePeriod_;
            uint64_t stepFraction = tTest%samplePeriod_;

            // Get staircase value
            float stairValue = startValue_  + stepCount*stepValue_;
            stairValue = max(stairValue, minValue_);
            stairValue = min(stairValue, maxValue_);

            // Add squarewave component
            if (stepFraction <= halfSamplePeriod_)
            {
                value = stairValue + amplitude_;
            }
            else
            {
                value = stairValue - amplitude_;
            }
        }
        return value;
    }


    void SquareWaveTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            jsonDatPrm.set(StartValueKey, startValue_, JsonFloatDecimals);
            jsonDatPrm.set(FinalValueKey, finalValue_, JsonFloatDecimals);
            jsonDatPrm.set(StepValueKey, stepValue_, JsonFloatDecimals);
            jsonDatPrm.set(AmplitudeKey, amplitude_, JsonFloatDecimals);
        }
    }


    ReturnStatus SquareWaveTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setStepValueFromJson(jsonMsgPrm,jsonDatPrm,status);
        setAmplitudeFromJson(jsonMsgPrm,jsonDatPrm,status);
        return status;
    }

    // Protected methods
    // --------------------------------------------------------------------------------------------
    
    void SquareWaveTest::updateDoneTime()
    {
        if (stepValue_ > 0.0) 
        {
            uint64_t numSteps_ = uint64_t(ceil(fabs(finalValue_ - startValue_)/stepValue_) + 1);
            uint64_t testDuration = numSteps_*uint64_t(samplePeriod_);
            doneTime_ = quietTime_ + testDuration;
        }
        else
        {
            numSteps_ = 0;
            doneTime_ = quietTime_;
        }
    }

    void SquareWaveTest::updateMaxMinValues()
    {
        maxValue_ = max(startValue_,finalValue_);
        minValue_ = min(startValue_,finalValue_);
    }

    void SquareWaveTest::setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(StartValueKey))
        {
            if (jsonMsgPrm[StartValueKey].is<float>())
            {
                setStartValue(jsonMsgPrm.get<float>(StartValueKey));
                jsonDatPrm.set(StartValueKey,getStartValue(),JsonFloatDecimals);
            }
            else if (jsonMsgPrm[StartValueKey].is<long>())
            {
                setStartValue(float(jsonMsgPrm.get<long>(StartValueKey)));
                jsonDatPrm.set(StartValueKey,getStartValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = StartValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void SquareWaveTest::setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(FinalValueKey))
        {
            if (jsonMsgPrm[FinalValueKey].is<float>())
            {
                setFinalValue(jsonMsgPrm.get<float>(FinalValueKey));
                jsonDatPrm.set(FinalValueKey,getFinalValue(),JsonFloatDecimals);
            }
            else if (jsonMsgPrm[FinalValueKey].is<long>())
            {
                setFinalValue(float(jsonMsgPrm.get<long>(FinalValueKey)));
                jsonDatPrm.set(FinalValueKey,getFinalValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = FinalValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }

    void SquareWaveTest::setStepValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(StepValueKey))
        {
            if (jsonMsgPrm[StepValueKey].is<float>())
            {
                setStepValue(jsonMsgPrm.get<float>(StepValueKey));
                jsonDatPrm.set(StepValueKey,getStepValue(),JsonFloatDecimals);
            }
            else if (jsonMsgPrm[StepValueKey].is<long>())
            {
                setStepValue(float(jsonMsgPrm.get<long>(StepValueKey)));
                jsonDatPrm.set(StepValueKey,getStepValue(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = StepValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void SquareWaveTest::setAmplitudeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(AmplitudeKey))
        {
            if (jsonMsgPrm[AmplitudeKey].is<float>())
            {
                setAmplitude(jsonMsgPrm.get<float>(AmplitudeKey));
                jsonDatPrm.set(AmplitudeKey,getAmplitude(),JsonFloatDecimals);
            }
            else if (jsonMsgPrm[AmplitudeKey].is<long>()) 
            {
                setAmplitude(float(jsonMsgPrm.get<long>(AmplitudeKey)));
                jsonDatPrm.set(AmplitudeKey,getAmplitude(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = AmplitudeKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }
 
} // namespace ps
