#include "ps_cyclic_test.h"

namespace ps
{

    // Public methods
    CyclicTest &CyclicTest::getInstance()
    {
        static CyclicTest cyclicTest;
        return cyclicTest;
    }

    void CyclicTest::setAmplitude(uint16_t amplitude)
    {
        amplitude_ = amplitude;
    }


    uint16_t CyclicTest::getAmplitude()
    {
        return amplitude_;
    }


    void CyclicTest::setOffset(uint16_t offset)
    {
        offset_ = offset;
    }


    uint16_t CyclicTest::getOffset()
    {
        return offset_;
    }


    void CyclicTest::setPeriod(uint64_t period)
    {
        period_ = period;
    }


    uint64_t CyclicTest::getPeriod()
    {
        return period_;
    }


    void CyclicTest::setLag(uint64_t lag)
    {
        lag_ = lag;
    }


    uint64_t CyclicTest::getLag()
    {
        return lag_;
    }


    uint16_t CyclicTest::getValue(uint64_t t)
    {
        uint64_t tmod = t%period_;

        int32_t value_int32 = 0;

        if (tmod < period_/2)
        {
           value_int32 += int32_t((uint64_t(4*amplitude_)*tmod)/period_);
           value_int32 += int32_t(offset_) - int32_t(amplitude_);
        }
        else
        {
           value_int32 += int32_t((uint64_t(4*amplitude_)*(period_ - tmod))/period_);
           value_int32 += int32_t(offset_) - int32_t(amplitude_);
        }
        return uint16_t(constrain(value_int32, 0, AnalogSubsystem::MaxValueDAC));
    }

    uint16_t CyclicTest::getPeriodCount(uint64_t t)
    {
        return uint16_t(t/period_);
    }

    // Private methods
    CyclicTest::CyclicTest() {}
}
