#ifndef PS_CURR_RANGE_H
#define PS_CURR_RANGE_H
#include <Arduino.h>
#include "ps_fixed_vector.h"
#include "ps_gains.h"

namespace ps
{

    class CurrRange
    {

        public:

            CurrRange() {};

            CurrRange(String name, float minCurr, float maxCurr, CurrGainPath gainPath, uint16_t maxAin);

            String name() const;
            float minCurr() const;
            float maxCurr() const;
            uint16_t maxAin() const;
            CurrGainPath gainPath() const;
            String gainPathString() const;

            float ainToCurr(uint16_t ain);
            uint16_t CurrToAin(float curr);

        protected:

            String name_;
            float minCurr_;
            float maxCurr_;
            CurrGainPath gainPath_;
            uint16_t maxAin_;

    };

    extern const CurrRange CurrRange1uA; 
    extern const CurrRange CurrRange10uA; 
    extern const CurrRange CurrRange100uA; 
    extern const CurrRange CurrRange1000uA; 

    const int NumCurrRange = 4;

    class CurrRangeFixedVector : public FixedVector<CurrRange,NumCurrRange>
    {
        public:
            CurrRangeFixedVector();
    };

    extern CurrRangeFixedVector CurrRangeVector;

} // namesapce ps

#endif
