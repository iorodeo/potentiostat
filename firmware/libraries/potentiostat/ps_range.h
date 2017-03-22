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


    template<typename GainType, typename IntType>
    Range<GainType,IntType>::Range(String name, float minValue, float maxValue, GainType gain, IntType maxInt)
        : name_(name), minValue_(minValue), maxValue_(maxValue), gain_(gain), maxInt_(maxInt)
    {}

    template<typename GainType, typename IntType>
    String Range<GainType,IntType>::name() const
    {
        return name_;
    }

    template<typename GainType, typename IntType>
    float Range<GainType,IntType>::minValue() const
    {
        return minValue_;
    }

    template<typename GainType, typename IntType>
    float Range<GainType,IntType>::maxValue() const
    {
        return maxValue_;
    }

    template<typename GainType, typename IntType>
    GainType Range<GainType,IntType>::gain() const
    {
        return gain_;
    }

    template<typename GainType, typename IntType>
    IntType Range<GainType,IntType>::maxInt() const
    {
        return maxInt_;
    }

    template<typename GainType, typename IntType>
    inline IntType Range<GainType,IntType>::valueToInt(float volt) const
    {
        IntType value = IntType(float(maxInt_)/(maxValue_ - minValue_)*(maxValue_ - volt));
        return constrain(value,0,maxInt_);
    }

    template<typename GainType, typename IntType>
    inline float Range<GainType,IntType>::intToValue(IntType value) const
    {
        return maxValue_ - (float(value)/float(maxInt_))*(maxValue_ - minValue_);
    }

}

#endif
