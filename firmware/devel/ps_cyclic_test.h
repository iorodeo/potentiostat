#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H
#include <Arduino.h>
#include "ps_analog_subsystem.h"

namespace ps
{

    class CyclicTest
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

            float getValue(double t) const;

            bool isDone(double t) const;


        private:

            float amplitude_ = DefaultAmplitude;     // 12-bit Dac int
            float offset_ = DefaultOffset;           // 12-bit Dac int
            float period_ = DefaultPeriod;           // Waveform period (s)
            float lag_ = DefaultLag;                 // Waveform lag    (s)
            uint16_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform

    };

} // namespace ps

//std::function<float(double)> voltFunc = std::bind(&CyclicTest::getValue, &cyclicTest, std::placeholders::_1);
//std::function<bool(double)>  isDoneFunc = std::bind(&CyclicTest::isDone, &cyclicTest, std::placeholders::_1);



#endif
