#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H
#include <Arduino.h>
#include "ps_analog_subsystem.h"

namespace ps
{

    class CyclicTest
    {
        public:

            static const uint16_t DefaultAmplitude = AnalogSubsystem::MidValueDAC;
            static const uint16_t DefaultOffset = AnalogSubsystem::MidValueDAC;
            static const uint64_t DefaultPeriod = UINT64_C(5000000);
            static const uint64_t DefaultLag = UINT64_C(0);

            static CyclicTest &getInstance();

            void setAmplitude(uint16_t amplitude);
            uint16_t getAmplitude();

            void setOffset(uint16_t offset);
            uint16_t getOffset();

            void setPeriod(uint64_t period);
            uint64_t getPeriod();

            void setLag(uint64_t lag);
            uint64_t getLag();

            uint16_t getValue(uint64_t t);

            uint16_t getPeriodCount(uint64_t t);

        private:

            CyclicTest();

            uint16_t amplitude_ = DefaultAmplitude;  // 12-bit DAC int
            uint16_t offset_ = DefaultOffset;        // 12-bit DAC int
            uint64_t period_ = DefaultPeriod;        // waveform period (us)
            uint64_t lag_ = DefaultLag;              // waveform lag    (us)

    };

}

#endif
