#ifndef PS_VOLT_RANGE_H
#define PS_VOLT_RANGE_H
#include <Arduino.h>
#include "ps_fixed_vector.h"
#include "ps_gains.h"

namespace ps
{

    class VoltRange
    {

        public:

            VoltRange() {};

            VoltRange(String name, float minVolt, float maxVolt, VoltGain voltGain, uint16_t maxDac);

            String name() const;
            float minVolt() const;
            float maxVolt() const;
            uint16_t maxDac() const;
            VoltGain voltGain() const;
            String voltGainString() const;

            uint16_t voltToDac(float volt) const;
            float dacToVolt(uint16_t value) const;

        protected:

            String name_ = String("default");
            float minVolt_ = -1.0;
            float maxVolt_ =  1.0;
            VoltGain voltGain_ = VoltGain1X;
            uint16_t maxDac_ = 4095;

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
