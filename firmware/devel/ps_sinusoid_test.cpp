#include "ps_sinusoid_test.h"
#include <cmath>

namespace ps
{ 

    const String SinusoidTest::NameString = String("Sinusoid Test");

    SinusoidTest::SinusoidTest() 
    {};

    //float SinusoidTest::getValue(uint64_t t) const
    //{
    //    uint64_t tmod = (t-lag_)%period_;
    //    return amplitude_*sin(2.0*M_PI*float(tmod)/float(period_)) + offset_;
    //}

    float SinusoidTest::getValue(uint64_t t) const
    {
        uint64_t tmod = (t-lag_)%period_;
        size_t k = (tmod*LookupTableSize)/period_;
        float s =  float(tmod*LookupTableSize)/float(period_)- float(k);
        float value = (lookupTable_[k+1] - lookupTable_[k])*s + lookupTable_[k];
        return value;
    }

    void SinusoidTest::updateLookupTable()
    {
        for (uint32_t i=0; i<LookupTableSize; i++)
        {
            float s = float(i)/float(LookupTableSize);
            lookupTable_[i] = amplitude_*sin(2.0*M_PI*s) + offset_;
        }

    }

 
} // nanespace ps
