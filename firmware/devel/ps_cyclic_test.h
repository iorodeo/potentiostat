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
            static constexpr uint64_t DefaultPeriod = UINT64_C(1000000);
            static constexpr uint64_t DefaultLag = UINT64_C(0);
            static constexpr uint32_t DefaultNumCycles = UINT32_C(1);
            static const String NameString; 

            CyclicTest();

            void setAmplitude(float amplitude);
            float getAmplitude() const;

            void setOffset(float offset);
            float getOffset() const;

            void setPeriod(uint64_t period);
            uint64_t getPeriod() const;

            void setLag(uint64_t lag);
            uint64_t getLag() const;

            void setNumCycles(uint32_t numCycles);
            uint32_t getNumCycles() const;

            uint32_t getCycleCount(uint64_t t) const;

            virtual bool isDone(uint64_t t) const;

            virtual float getValue(uint64_t t) const;
            
            virtual float getMaxValue() const;

            virtual float getMinValue() const;


        private:

            float amplitude_ = DefaultAmplitude;     // 12-bit Dac int
            float offset_ = DefaultOffset;           // 12-bit Dac int
            uint64_t period_ = DefaultPeriod;        // Waveform period (us)
            uint64_t lag_ = DefaultLag;              // Waveform lag    (us)
            uint32_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform


    };

} // namespace ps




#endif
