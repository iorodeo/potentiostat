#include "ps_cyclic_test.h"
#include <math.h>

namespace ps
{
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


    void CyclicTest::setPeriod(float period)
    {
        period_ = period;
    }


    float CyclicTest::getPeriod() const
    {
        return period_;
    }


    void CyclicTest::setLag(float lag)
    {
        lag_ = constrain(lag,-1.0,1.0);
    }


    float CyclicTest::getLag() const
    {
        return lag_;
    }


    void CyclicTest::setNumCycles(uint16_t numCycles)
    {
        numCycles_ = numCycles;
    }


    uint16_t CyclicTest::getNumCycles() const
    {
        return numCycles_;
    }


    float CyclicTest::getCycleCount(double t) const
    {
        return float(t/double(period_));
    }


    float CyclicTest::getCycleFrac(double t) const
    {
        float cycleCount = getCycleCount(t) - lag_;
        return cycleCount - floor(cycleCount);
    }


    float CyclicTest::getValue(double t) const
    {
        float value = 0.0;
        float s = getCycleFrac(t);

        if (s < 0.5)
        {
            value = 2.0*amplitude_*s + offset_ - 0.5*amplitude_;
        }
        else
        {
            value = 2.0*amplitude_*(1.0 - s) + offset_ - 0.5*amplitude_;
        }
        return value;
    }


    bool CyclicTest::isDone(double t) const
    {
        bool done = false;
        float cycleCount = getCycleCount(t);
        if (cycleCount >= numCycles_)
        {
            done = true;
        }
        return done;
    }


} // namespace ps
