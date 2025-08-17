#include "ps_differential_pulse_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"
#include <math.h>

namespace ps 
{
    // Public methods
    // --------------------------------------------------------------------------------------------
    DifferentialPulseTest::DifferentialPulseTest()
    { 
        setName("differentialPulse");
        setMuxCompatible(false);
        setSampleMethod(SampleCustom);
        updateStepSign();
        updateDoneTime();
        updateMaxMinValues();
    };

    void DifferentialPulseTest::setStartValue(float value)
    {
        startValue_ = value;
        updateStepSign();
        updateDoneTime();
        updateMaxMinValues();
    }


    float DifferentialPulseTest::getStartValue()
    {
        return startValue_;
    }


    void DifferentialPulseTest::setFinalValue(float value)
    {
        finalValue_ = value;
        updateStepSign();
        updateDoneTime();
        updateMaxMinValues();
    }


    float DifferentialPulseTest::getFinalValue()
    {
        return finalValue_;
    }


    void DifferentialPulseTest::setStepValue(float value)
    {
        stepValue_ = fabs(value);
        updateDoneTime();
    }


    float DifferentialPulseTest::getStepValue()
    {
        return stepValue_;
    }


    void DifferentialPulseTest::setPulseValue(float value)
    {
        pulseValue_ = fabs(value);
    }


    float DifferentialPulseTest::getPulseValue()
    {
        return pulseValue_;
    }


    void DifferentialPulseTest::setWindow(float value)
    {
        window_ = fabs(value);
        window_ = max(0.0, window_);
        window_ = min(1.0, window_);
        updateWindowLenUs();
    }


    float DifferentialPulseTest::getWindow()
    {
        return window_;
    }


    float DifferentialPulseTest::getMaxValue() const 
    {
        float maxOutputValue = 0.0;
        if (stepSign_ > 0) 
        {
            maxOutputValue = maxValue_ + pulseValue_;
        }
        else 
        {
            maxOutputValue = maxValue_;
        }
        return maxOutputValue;
    }


    float DifferentialPulseTest::getMinValue() const 
    {
        float minOutputValue = 0.0;
        if (stepSign_ < 0) 
        {
            minOutputValue = minValue_ - pulseValue_;
        }
        else 
        {
            minOutputValue = minValue_;
        }
        return minOutputValue;
    }


    void DifferentialPulseTest::setSamplePeriod(uint64_t samplePeriod)
    {
        BaseTest::setSamplePeriod(samplePeriod);
        halfSamplePeriod_ = samplePeriod >> 1;
        updateDoneTime();
        updateWindowLenUs();
    }

    bool DifferentialPulseTest::isDone(uint64_t t) const 
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


    uint64_t DifferentialPulseTest::getDoneTime() const
    {
        return doneTime_;

    }

    void DifferentialPulseTest::reset()
    {
        numForward_ = 0;
        numReverse_ = 0;
        currForward_ = 0.0;
        currReverse_ = 0.0;
        currReverseLast_ = 0.0;
        testCnt_ = 0;
        isFirst_ = true;
    }


    float DifferentialPulseTest::getValue(uint64_t t) const 
    {
        float value = 0.0;
        if ( t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            uint64_t stepModPos = (t - quietTime_)%samplePeriod_;
            uint64_t stepCount = getStepCount(t);
            float stairValue = getStairValue(t);

            if (stepCount ==0) {
                value = stairValue;
            }
            else {
                if (stepModPos < halfSamplePeriod_)
                {
                    value = stairValue + pulseValue_;
                }
                else
                {
                    value = stairValue;
                }
            }

        }
        return value;
    }


    float DifferentialPulseTest::getStairValue(uint64_t t) const
    {
        float stairValue = 0.0;
        if (t < quietTime_)
        {
            stairValue = quietValue_;
        }
        else
        {
            uint64_t stepCount = getStepCount(t);
            stairValue = startValue_ + stepCount*stepSign_*stepValue_;
            stairValue = max(stairValue, minValue_);
            stairValue = min(stairValue, maxValue_);
        }
        return stairValue;
    } 
    

    uint64_t DifferentialPulseTest::getStepCount(uint64_t t) const 
    { 
        uint64_t tTest = t - quietTime_; 
        return tTest/samplePeriod_;
    }


    bool DifferentialPulseTest::updateSample(Sample sampleRaw, Sample &sampleTest) 
    {
        bool newSample = false;

        if (sampleRaw.t < quietTime_)
        {
            if ((testCnt_ > 0) && (testCnt_%sampleModulus_==0))
            {
                sampleTest.t = sampleRaw.t;
                sampleTest.volt = quietValue_;
                sampleTest.curr =  0.0;
                newSample = true;
            }
            testCnt_++;
        }
        else 
        {
            if (isFirst_)
            {
                isFirst_ = false;
                testCnt_ = 0;
            }

            uint64_t tTest = (sampleRaw.t - quietTime_);
            uint64_t stepModPos = tTest%samplePeriod_;

            if (stepModPos < halfSamplePeriod_)
            {
                // forward step
                if ((halfSamplePeriod_ - stepModPos - 1) < windowLenUs_)
                {
                    numForward_++;
                    currForward_ += sampleRaw.curr;
                }
            }
            else
            {
                // reverse step
                if ((samplePeriod_ - stepModPos - 1) < windowLenUs_)
                {
                    numReverse_++;
                    currReverse_ += sampleRaw.curr;
                }
            }

            if ((testCnt_ > 0) && (testCnt_%sampleModulus_==0))
            {
                currForward_ /= numForward_;
                currReverse_ /= numReverse_;

                sampleTest.t = sampleRaw.t; //- halfSamplePeriod_;
                sampleTest.volt = getStairValue(sampleRaw.t);
                if (tTest > samplePeriod_) 
                {
                    sampleTest.curr = currForward_ - currReverseLast_;
                }
                else 
                {
                    sampleTest.curr = 0.0;
                   
                }
                currReverseLast_ = currReverse_;
                numForward_ = 0;
                numReverse_ = 0;
                currForward_ = 0.0;
                currReverse_ = 0.0;
                newSample = true;
            }
            testCnt_++;
        }

        return newSample; 
    }


    void DifferentialPulseTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            jsonDatPrm.set(StartValueKey, startValue_);
            jsonDatPrm.set(FinalValueKey, finalValue_);
            jsonDatPrm.set(StepValueKey, stepValue_);
            jsonDatPrm.set(PulseValueKey, pulseValue_);
            jsonDatPrm.set(WindowKey, window_);
        }
    }


    ReturnStatus DifferentialPulseTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setPulseValueFromJson(jsonMsgPrm,jsonDatPrm,status);
        setWindowFromJson(jsonMsgPrm,jsonDatPrm,status);
        return status;
    }

    // Protected methods
    // --------------------------------------------------------------------------------------------
   
    void DifferentialPulseTest::updateDoneTime()
    {
        if (stepValue_ > 0.0) 
        {
            uint64_t numSteps_ = uint64_t(ceil(fabs(finalValue_ - startValue_)/stepValue_))+1;
            uint64_t testDuration = numSteps_*uint64_t(samplePeriod_);
            doneTime_ = quietTime_ + testDuration; 
        }
        else
        {
            doneTime_ = quietTime_;
        }
    }


    void DifferentialPulseTest::updateMaxMinValues()
    {
        maxValue_ = max(startValue_,finalValue_);
        minValue_ = min(startValue_,finalValue_);
    }


    void DifferentialPulseTest::updateWindowLenUs()
    {
        windowLenUs_ = uint64_t((halfSamplePeriod_- 1)*window_);
        windowLenUs_ = min(halfSamplePeriod_- 1, windowLenUs_);
        windowLenUs_ = max(uint64_t(1), windowLenUs_);
    }


    void DifferentialPulseTest::updateStepSign()
    {
        stepSign_ = (startValue_ <= finalValue_) ? 1.0 : -1.0;
    }


    void DifferentialPulseTest::setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
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


    void DifferentialPulseTest::setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
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

    void DifferentialPulseTest::setStepValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(StepValueKey))
        {
            if (jsonMsgPrm[StepValueKey].is<float>())
            {
                setStepValue(jsonMsgPrm.get<float>(StepValueKey));
                jsonDatPrm.set(StepValueKey,getStepValue());
            }
            else if (jsonMsgPrm[StepValueKey].is<long>())
            {
                setStepValue(float(jsonMsgPrm.get<long>(StepValueKey)));
                jsonDatPrm.set(StepValueKey,getStepValue());
            }
            else
            {
                status.success = false;
                String errorMsg = StepValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void DifferentialPulseTest::setPulseValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(PulseValueKey))
        {
            if (jsonMsgPrm[PulseValueKey].is<float>())
            {
                setPulseValue(jsonMsgPrm.get<float>(PulseValueKey));
                jsonDatPrm.set(PulseValueKey,getPulseValue());
            }
            else if (jsonMsgPrm[PulseValueKey].is<long>()) 
            {
                setPulseValue(float(jsonMsgPrm.get<long>(PulseValueKey)));
                jsonDatPrm.set(PulseValueKey,getPulseValue());
            }
            else
            {
                status.success = false;
                String errorMsg = PulseValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }

    void DifferentialPulseTest::setWindowFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(WindowKey))
        {
            if (jsonMsgPrm[WindowKey].is<float>())
            {
                setWindow(jsonMsgPrm.get<float>(WindowKey));
                jsonDatPrm.set(WindowKey,getWindow());
            }
            else if (jsonMsgPrm[WindowKey].is<long>()) 
            {
                setWindow(float(jsonMsgPrm.get<long>(WindowKey)));
                jsonDatPrm.set(WindowKey,getWindow());
            }
            else
            {
                status.success = false;
                String errorMsg = WindowKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }
 
} // namespace ps
