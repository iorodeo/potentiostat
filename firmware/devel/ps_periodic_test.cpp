#include "ps_periodic_test.h"
#include "ps_time_utils.h"

namespace ps
{ 
    const String PeriodicTest::AmplitudeKey = String("amplitude");
    const String PeriodicTest::OffsetKey = String("offset");
    const String PeriodicTest::PeriodKey = String("period");
    const String PeriodicTest::NumCyclesKey = String("numCycles");
    const String PeriodicTest::ShiftKey = String("shift");


    PeriodicTest::PeriodicTest() 
    { 
        updateShiftInUs();
        setName("period");
    }


    void PeriodicTest::setAmplitude(float amplitude)
    {
        amplitude_ = amplitude;
    }


    float PeriodicTest::getAmplitude() const
    {
        return amplitude_;
    }


    void PeriodicTest::setOffset(float offset)
    {
        offset_ = offset;
    }


    float PeriodicTest::getOffset() const
    {
        return offset_;
    }


    void PeriodicTest::setPeriod(uint64_t period)
    {
        period_ = period;
        updateShiftInUs();
    }


    uint64_t PeriodicTest::getPeriod() const
    {
        return period_;
    }


    void PeriodicTest::setShift(float shift)
    {
        shift_ = shift;
        updateShiftInUs();
    }


    float PeriodicTest::getShift() const
    {
        return shift_;
    }


    void PeriodicTest::setNumCycles(uint32_t numCycles)
    {
        numCycles_ = numCycles;
    }


    uint32_t PeriodicTest::getNumCycles() const
    {
        return numCycles_;
    }


    uint32_t PeriodicTest::getCycleCount(uint64_t t) const
    {
        if (t < quietTime_)
        {
            return 0;
        }
        else
        {
            return uint32_t((t-quietTime_)/period_);
        }
    }


    bool PeriodicTest::isDone(uint64_t t) const
    {
        bool done = false;
        uint32_t cycleCount = getCycleCount(t);
        if (cycleCount >= numCycles_)
        {
            done = true;
        }
        return done;
    }


    float PeriodicTest::getValue(uint64_t t) const
    {
        return 0.0;
    }


    float PeriodicTest::getMaxValue() const
    {
        return offset_ + 0.5*amplitude_;
    }


    float PeriodicTest::getMinValue() const
    {
        return offset_ - 0.5*amplitude_;
    }


    void PeriodicTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);
        jsonDat.set(AmplitudeKey, amplitude_, JsonFloatDecimals);
        jsonDat.set(OffsetKey, offset_, JsonFloatDecimals);
        jsonDat.set(PeriodKey, convertUsToMs(period_));
        jsonDat.set(NumCyclesKey, numCycles_);
        jsonDat.set(ShiftKey, shift_, JsonFloatDecimals);
    }

    ReturnStatus PeriodicTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setAmplitudeFromJson(jsonPrm,jsonDat,status);
        setOffsetFromJson(jsonPrm,jsonDat,status);
        setPeriodFromJson(jsonPrm,jsonDat,status);
        setNumCyclesFromJson(jsonPrm,jsonDat,status);
        setShiftFromJson(jsonPrm,jsonDat,status);

        return status;
    }


    // Protected Methods
    // ------------------------------------------------------------------------
    
    void PeriodicTest::setAmplitudeFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(AmplitudeKey))
        {
            if (jsonPrm[AmplitudeKey].is<float>())
            {
                setAmplitude(jsonPrm.get<float>(AmplitudeKey));
                jsonDat.set(AmplitudeKey,getAmplitude(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = AmplitudeKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setOffsetFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(OffsetKey))
        {
            if (jsonPrm[OffsetKey].is<float>())
            {
                setOffset(jsonPrm.get<float>(OffsetKey));
                jsonDat.set(OffsetKey,getOffset(),JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = OffsetKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setPeriodFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(PeriodKey))
        {
            if (jsonPrm[PeriodKey].is<unsigned long>())
            {
                setPeriod(convertMsToUs(jsonPrm.get<unsigned long>(PeriodKey)));
                jsonDat.set(PeriodKey,convertUsToMs(getPeriod()));
            }
            else
            {
                status.success = false;
                String errorMsg = PeriodKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setNumCyclesFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(NumCyclesKey))
        {
            if (jsonPrm[NumCyclesKey].is<unsigned long>())
            {
                setNumCycles(jsonPrm.get<unsigned long>(NumCyclesKey));
                jsonDat.set(NumCyclesKey,getNumCycles());
            }
            else
            {
                status.success = false;
                String errorMsg = NumCyclesKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setShiftFromJson(JsonObject &jsonPrm, JsonObject &jsonDat, ReturnStatus &status)
    {
        if (jsonPrm.containsKey(ShiftKey))
        {
            if (jsonPrm[ShiftKey].is<float>())
            {
                float shiftTmp = jsonPrm.get<float>(ShiftKey);
                if ((shiftTmp >= 0.0) || (shiftTmp <= 1.0))
                {
                    setShift(shiftTmp);
                    jsonDat.set(ShiftKey,getShift(),JsonFloatDecimals);
                }
                else
                {
                    status.success = false;
                    String errorMsg = ShiftKey + String(" out of range");
                    status.appendToMessage(errorMsg);
                }
            }
            else
            {
                status.success = false;
                String errorMsg = ShiftKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::updateShiftInUs()
    {
        shiftInUs_ = uint64_t(double(shift_)*period_);
    }

}
