#include "ps_cyclic_test.h"
#include <math.h>

namespace ps
{
    const String CyclicTest::NameString = String("Cyclic Voltammetry"); 

    CyclicTest::CyclicTest() 
    { }


    void CyclicTest::setAmplitude(float amplitude)
    {
        amplitude_ = amplitude;
    }


    float CyclicTest::getAmplitude() const
    {
        return amplitude_;
    }


    void CyclicTest::setOffset(float offset)
    {
        offset_ = offset;
    }


    float CyclicTest::getOffset() const
    {
        return offset_;
    }


    void CyclicTest::setPeriod(uint64_t period)
    {
        period_ = period;
    }


    uint64_t CyclicTest::getPeriod() const
    {
        return period_;
    }


    void CyclicTest::setLag(uint64_t lag)
    {
        lag_ = lag;
    }


    uint64_t CyclicTest::getLag() const
    {
        return lag_;
    }


    void CyclicTest::setNumCycles(uint32_t numCycles)
    {
        numCycles_ = numCycles;
    }


    uint32_t CyclicTest::getNumCycles() const
    {
        return numCycles_;
    }


    uint32_t CyclicTest::getCycleCount(uint64_t t) const
    {
        return uint32_t(t/period_);
    }


    bool CyclicTest::isDone(uint64_t t) const
    {
        bool done = false;
        uint32_t cycleCount = getCycleCount(t);
        if (cycleCount >= numCycles_)
        {
            done = true;
        }
        return done;
    }


    float CyclicTest::getValue(uint64_t t) const
    {
        float value = 0.0;
        uint64_t s = t%period_;
        uint64_t halfPeriod = period_ >> 1;

        if (s < halfPeriod) 
        {
            value = (2.0*amplitude_*s)/period_ + offset_ - 0.5*amplitude_;
        }
        else
        {
            value = (2.0*amplitude_*(period_ - s))/period_ + offset_ - 0.5*amplitude_;
        }
        return value;
    };


    float CyclicTest::getMaxValue() const
    {
        return offset_ + 0.5*amplitude_;
    }


    float CyclicTest::getMinValue() const
    {
        return offset_ - 0.5*amplitude_;
    }


} // namespace ps
