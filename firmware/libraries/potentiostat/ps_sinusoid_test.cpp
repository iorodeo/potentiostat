#include "ps_sinusoid_test.h"
#include <math.h>

namespace ps
{ 

    SinusoidTest::SinusoidTest() : PeriodicTest()
    {
        updateLookupTable();
        setName("sinusoid");
        setMuxCompatible(true);
    }


    void SinusoidTest::setAmplitude(float amplitude)
    {
        PeriodicTest::setAmplitude(amplitude);
        updateLookupTable();
    }


    void SinusoidTest::setOffset(float offset)
    {
        PeriodicTest::setOffset(offset);
        updateLookupTable();
    }


    float SinusoidTest::getValue(uint64_t t) const
    {
        float value = 0.0;
        if (t < quietTime_)
        {
            value = quietValue_;
        }
        else
        {
            uint64_t tmod = (t - quietTime_ + shiftInUs_)%period_;
            float pos =  float(tmod*(LookupTableSize-1))/float(period_);
            value = lookupTable_.getValue(pos);
        }
        return value;
    }


    void SinusoidTest::updateLookupTable()
    {
        for (uint32_t i=0; i<LookupTableSize; i++)
        {
            float s = float(i)/float(LookupTableSize-1);
            lookupTable_[i] = amplitude_*sin(2.0*M_PI*s) + offset_;
        }

    }

 
} // nanespace ps
