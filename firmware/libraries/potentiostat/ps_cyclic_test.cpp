#include "ps_cyclic_test.h"
#include <math.h>

namespace ps
{

    CyclicTest::CyclicTest() : PeriodicTest()
    {
        setName("cyclic");
        setMuxCompatible(true);
    }


    float CyclicTest::getValue(uint64_t t) const
    {
        float value = 0.0;
        if ( t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            uint64_t s = (t - quietTime_ + shiftInUs_)%period_;
            uint64_t halfPeriod = period_ >> 1;

            if (s < halfPeriod) 
            {
                value = (4.0*amplitude_*s)/period_ + offset_ - amplitude_;
            }
            else
            {
                value = (4.0*amplitude_*(period_ - s))/period_ + offset_ - amplitude_;
            }
        }
        return value;
    }


} // namespace ps
