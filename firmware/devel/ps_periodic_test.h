#ifndef PS_PERIODIC_TEST_H
#define PS_PERIODIC_TEST_H
#include "ps_base_test.h"
#include "ps_constants.h"

namespace ps
{

    class PeriodicTest : public BaseTest
    {
        public:

            static constexpr float DefaultAmplitude = 1.0; 
            static constexpr float DefaultOffset = 0.0; 
            static constexpr uint64_t DefaultPeriod = UINT64_C(1000000);
            static constexpr uint64_t DefaultLag = UINT64_C(0);
            static constexpr uint32_t DefaultNumCycles = UINT32_C(1);
            static const String NameString; 

            PeriodicTest();

            virtual void setAmplitude(float amplitude);
            virtual float getAmplitude() const;

            virtual void setOffset(float offset);
            virtual float getOffset() const;

            virtual void setPeriod(uint64_t period);
            virtual uint64_t getPeriod() const;

            virtual void setLag(uint64_t lag);
            virtual uint64_t getLag() const;

            virtual void setNumCycles(uint32_t numCycles);
            virtual uint32_t getNumCycles() const;

            virtual uint32_t getCycleCount(uint64_t t) const;

            virtual bool isDone(uint64_t t) const;
            virtual float getValue(uint64_t t) const;
            virtual float getMaxValue() const;
            virtual float getMinValue() const;

        protected:

            float amplitude_ = DefaultAmplitude;     // 12-bit Dac int
            float offset_ = DefaultOffset;           // 12-bit Dac int
            uint64_t period_ = DefaultPeriod;        // Waveform period (us)
            uint64_t lag_ = DefaultLag;              // Waveform lag    (us)
            uint32_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform


    };


}

#endif
