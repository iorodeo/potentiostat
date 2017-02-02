#include "ps_periodic_test.h"

namespace ps
{

    const String PeriodicTest::NameString = String("Periodic Test Base"); 

    PeriodicTest::PeriodicTest() 
    { 
        updateShiftInUs();
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

    // Protected methods
    // ------------------------------------------------------------------------
    void PeriodicTest::updateShiftInUs()
    {
        shiftInUs_ = uint64_t(double(shift_)*period_);
    }

}
