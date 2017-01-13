#ifndef PS_VOLT_RANGE_H
#define PS_VOLT_RANGE_H
#include <Arduino.h>
#include "ps_range.h"
#include "ps_fixed_vector.h"
#include "ps_gains.h"

namespace ps
{
    class VoltRange : public Range<VoltGain,uint16_t> 
    {
        public: 
            VoltRange() : Range<VoltGain,uint16_t>()  {};

            VoltRange(String name, float minValue, float maxValue, VoltGain voltGain, uint16_t maxInt)
                : Range<VoltGain,uint16_t>(name, minValue, maxValue, voltGain, maxInt) {};
    
    };

    extern const VoltRange VoltRange1V; 
    extern const VoltRange VoltRange2V; 
    extern const VoltRange VoltRange5V; 
    extern const VoltRange VoltRange10V; 

    const int NumVoltRange = 4;

    class VoltRangeFixedVector : public FixedVector<VoltRange,NumVoltRange>
    {
        public:
            VoltRangeFixedVector();
    };

    extern VoltRangeFixedVector VoltRangeVector;

} // namespace ps

#endif
