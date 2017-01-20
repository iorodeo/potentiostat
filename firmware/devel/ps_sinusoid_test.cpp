#include "ps_sinusoid_test.h"
#include <cmath>

namespace ps
{ 

    const String SinusoidTest::NameString = String("Sinusoid Test");

    SinusoidTest::SinusoidTest() 
    {
        updateLookupTable();
    };

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
        uint64_t tmod = (t-lag_)%period_;
        float pos =  float(tmod*LookupTableSize)/float(period_);
        return lookupTable_.getValue(pos);
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
