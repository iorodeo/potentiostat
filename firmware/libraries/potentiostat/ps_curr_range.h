#ifndef PS_CURR_RANGE_H
#define PS_CURR_RANGE_H

#include <Arduino.h>
#include "ps_range.h"
#include "ps_gains.h"

namespace ps
{

    class CurrRange : public Range<CurrGainPath,uint16_t> 
    {
        public: 
            CurrRange() : Range<CurrGainPath,uint16_t>()  {};

            CurrRange(String name, float minValue, float maxValue, CurrGainPath currGainPath, uint16_t maxInt)
                : Range<CurrGainPath,uint16_t>(name, minValue, maxValue, currGainPath, maxInt) {};
    
    };

} 

#endif
