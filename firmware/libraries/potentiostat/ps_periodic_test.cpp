#include "ps_periodic_test.h"
#include "ps_time_utils.h"

namespace ps
{ 

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


    uint64_t PeriodicTest::getDoneTime() const 
    {
        return quietTime_ + numCycles_*period_;
    }


    float PeriodicTest::getValue(uint64_t t) const
    {
        return 0.0;
    }


    float PeriodicTest::getMaxValue() const
    {
        return offset_ + amplitude_;
    }


    float PeriodicTest::getMinValue() const
    {
        return offset_ - amplitude_;
    }


    void PeriodicTest::getParam(JsonObject &jsonDat)
    {
        BaseTest::getParam(jsonDat);

        ReturnStatus status;
        JsonObject &jsonDatPrm = getParamJsonObject(jsonDat,status);

        if (status.success)
        {
            jsonDatPrm.set(AmplitudeKey, amplitude_);
            jsonDatPrm.set(OffsetKey, offset_);
            jsonDatPrm.set(PeriodKey, convertUsToMs(period_));
            jsonDatPrm.set(NumCyclesKey, numCycles_);
            jsonDatPrm.set(ShiftKey, shift_);
        }
    }

    ReturnStatus PeriodicTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
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
        setAmplitudeFromJson(jsonMsgPrm,jsonDatPrm,status);
        setOffsetFromJson(jsonMsgPrm,jsonDatPrm,status);
        setPeriodFromJson(jsonMsgPrm,jsonDatPrm,status);
        setNumCyclesFromJson(jsonMsgPrm,jsonDatPrm,status);
        setShiftFromJson(jsonMsgPrm,jsonDatPrm,status);

        return status;
    }


    // Protected Methods
    // ------------------------------------------------------------------------
    
    void PeriodicTest::setAmplitudeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(AmplitudeKey))
        {
            if (jsonMsgPrm[AmplitudeKey].is<float>())
            {
                setAmplitude(jsonMsgPrm.get<float>(AmplitudeKey));
                jsonDatPrm.set(AmplitudeKey,getAmplitude());
            }
            else if (jsonMsgPrm[AmplitudeKey].is<long>()) 
            {
                setAmplitude(float(jsonMsgPrm.get<long>(AmplitudeKey)));
                jsonDatPrm.set(AmplitudeKey,getAmplitude());
            }
            else
            {
                status.success = false;
                String errorMsg = AmplitudeKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setOffsetFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(OffsetKey))
        {
            if (jsonMsgPrm[OffsetKey].is<float>())
            {
                setOffset(jsonMsgPrm.get<float>(OffsetKey));
                jsonDatPrm.set(OffsetKey,getOffset());
            }
            else if (jsonMsgPrm[OffsetKey].is<long>())
            {
                setOffset(float(jsonMsgPrm.get<long>(OffsetKey)));
                jsonDatPrm.set(OffsetKey,getOffset());
            }
            else
            {
                status.success = false;
                String errorMsg = OffsetKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setPeriodFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(PeriodKey))
        {
            if (jsonMsgPrm[PeriodKey].is<unsigned long>())
            {
                setPeriod(convertMsToUs(jsonMsgPrm.get<unsigned long>(PeriodKey)));
                jsonDatPrm.set(PeriodKey,convertUsToMs(getPeriod()));
            }
            else
            {
                status.success = false;
                String errorMsg = PeriodKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setNumCyclesFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(NumCyclesKey))
        {
            if (jsonMsgPrm[NumCyclesKey].is<unsigned long>())
            {
                setNumCycles(jsonMsgPrm.get<unsigned long>(NumCyclesKey));
                jsonDatPrm.set(NumCyclesKey,getNumCycles());
            }
            else
            {
                status.success = false;
                String errorMsg = NumCyclesKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }
    }


    void PeriodicTest::setShiftFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status)
    {
        if (jsonMsgPrm.containsKey(ShiftKey))
        {
            if (jsonMsgPrm[ShiftKey].is<float>() || jsonMsgPrm[ShiftKey].is<long>())
            {
                float shiftTmp = 0.0;
                if (jsonMsgPrm[ShiftKey].is<float>())
                { 
                    shiftTmp = jsonMsgPrm.get<float>(ShiftKey);
                }
                else
                { 
                    shiftTmp = float(jsonMsgPrm.get<long>(ShiftKey));
                }

                if ((shiftTmp >= 0.0) || (shiftTmp <= 1.0))
                {
                    setShift(shiftTmp);
                    jsonDatPrm.set(ShiftKey,getShift());
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
