#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H
#include <Arduino.h>
#include "ps_base_test.h"
#include "ps_analog_subsystem.h"

namespace ps
{

    class CyclicTest : public BaseTest
    {
        public:

            static constexpr float DefaultAmplitude = 1.0; 
            static constexpr float DefaultOffset = 0.0; 
            static constexpr float DefaultPeriod = 1.0;
            static constexpr float DefaultLag = 0.0;
            static constexpr uint16_t DefaultNumCycles = 1;
            static const String NameString; 

            CyclicTest();

            void setAmplitude(float amplitude);
            float getAmplitude() const;

            void setOffset(float offset);
            float getOffset() const;

            void setPeriod(float period);
            float getPeriod() const;

            void setLag(float lag);
            float getLag() const;

            void setNumCycles(uint16_t numCycles);
            uint16_t getNumCycles() const;

            float getCycleCount(double t) const;

            float getCycleFrac(double t) const;

            virtual float getValue(double t) const;

            virtual bool isDone(double t) const;

            virtual float getMaxValue() const;

            virtual float getMinValue() const;


        private:

            float amplitude_ = DefaultAmplitude;     // 12-bit Dac int
            float offset_ = DefaultOffset;           // 12-bit Dac int
            float period_ = DefaultPeriod;           // Waveform period (s)
            float lag_ = DefaultLag;                 // Waveform lag    (s)
            uint16_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform

    };

} // namespace ps




#endif
