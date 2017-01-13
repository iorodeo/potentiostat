#include "ps_cyclic_test.h"
#include <math.h>

namespace ps
{
    // TO DO ... modify CyclicTest to use floats instead of uint16_t this will be much clearer

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
        lag_ = lag;
    }


    float CyclicTest::getLag() const
    {
        return lag_;
    }

    float CyclicTest::getCycleCount(double t) const
    {
        return float(t/double(period_));
    }

    float CyclicTest::getCycleFrac(double t) const
    {
        float cycleCount = getCycleCount(t);
        return cycleCount - floor(cycleCount);
    }



    float CyclicTest::getValue(double t) const
    {
        float value = 0.0;
        float s = getCycleFrac(t);

        if (s < 0.5)
        {
            value = 4.0*amplitude_*s + offset_ - amplitude_;
        }
        else
        {
            value = 4.0*amplitude_*(1.0 - s) + offset_ - amplitude_;
        }
        return value;
    }


}
