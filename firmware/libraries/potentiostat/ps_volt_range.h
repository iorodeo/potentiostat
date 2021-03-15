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

    class VoltRangeDac : public VoltRange 
    {
        //using VoltRange::VoltRange;
        
        public: 
            VoltRangeDac() : VoltRange()  {};

            VoltRangeDac(String name, float minValue, float maxValue, VoltGain voltGain, uint16_t maxInt)
                : VoltRange(name, minValue, maxValue, voltGain, maxInt) {};
    };

    class VoltRangeAdc : public VoltRange 
    {
        //using VoltRange::VoltRange;
        
        public: 
            VoltRangeAdc() : VoltRange()  {};

            VoltRangeAdc(String name, float minValue, float maxValue, VoltGain voltGain, uint16_t maxInt)
                : VoltRange(name, minValue, maxValue, voltGain, maxInt) {};
    };

} 

#endif
