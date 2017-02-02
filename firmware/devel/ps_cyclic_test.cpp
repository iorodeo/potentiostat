#include "ps_cyclic_test.h"
#include <math.h>

namespace ps
{
    const String CyclicTest::NameString = String("Cyclic Voltammetry"); 


    CyclicTest::CyclicTest()
    {}


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
                value = (2.0*amplitude_*s)/period_ + offset_ - 0.5*amplitude_;
            }
            else
            {
                value = (2.0*amplitude_*(period_ - s))/period_ + offset_ - 0.5*amplitude_;
            }
        }
        return value;
    }

} // namespace ps
