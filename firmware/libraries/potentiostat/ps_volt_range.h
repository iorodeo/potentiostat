#ifndef PS_VOLT_RANGE_H
#define PS_VOLT_RANGE_H

#include <Arduino.h>
#include "ps_range.h"
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

} 

#endif
