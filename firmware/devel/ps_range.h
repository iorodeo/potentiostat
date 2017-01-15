#ifndef PS_RANGE_H
#define PS_RANGE_H

namespace ps
{

    template<typename GainType, typename IntType>
    class Range
    {
        public:

            Range() {};
            Range(String name, float minValue, float maxValue, GainType gain, IntType maxInt);
            String name() const;
            float minValue() const;
            float maxValue() const;
            GainType gain() const;
            IntType maxInt() const;
            inline IntType valueToInt(float volt) const;
            inline float intToValue(IntType value) const;

        private:

            String name_;
            float minValue_;
            float maxValue_;
            GainType gain_;
            IntType maxInt_;

    };

}

#include "ps_range_definitions.h"

#endif
