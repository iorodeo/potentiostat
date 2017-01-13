#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H
#include <Arduino.h>
#include "ps_analog_subsystem.h"

namespace ps
{
    // TO DO ... modify CyclicTest to use floats instead of uint16_t this will be much clearer

    class CyclicTest
    {
        public:

            static constexpr float DefaultAmplitude = 1.0; 
            static constexpr float DefaultOffset = 0.0; 
            static constexpr float DefaultPeriod = 1.0;
            static constexpr float DefaultLag = 0.0;
            static const uint16_t DefaultNumCycles = 1;

            CyclicTest() {};

            void setAmplitude(float amplitude);
            float getAmplitude() const;

            void setOffset(float offset);
            float getOffset() const;

            void setPeriod(float period);
            float getPeriod() const;

            void setLag(float lag);
            float getLag() const;

            float getCycleCount(double t) const;

            float getCycleFrac(double t) const;

            float getValue(double t) const;

        private:

            float amplitude_ = DefaultAmplitude;  // 12-bit Dac int
            float offset_ = DefaultOffset;        // 12-bit Dac int
            float period_ = DefaultPeriod;        // Waveform period (us)
            float lag_ = DefaultLag;              // Waveform lag    (us)
            uint16_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform

    };



} // namespace ps

//std::function<float(uint16_t)> valueFunc = std::bind(&CyclicTest::getValue, &cyclicTest, std::placeholders::_1);

#endif
