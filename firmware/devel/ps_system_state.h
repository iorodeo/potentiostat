#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H
#include <Arduino.h>
#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include "ps_circular_buffer.h"
#include "ps_voltammetry.h"
#include "ps_sample.h"
#include "ps_filter.h"

namespace ps
{

    class SystemState
    {

        public:

            SystemState();
            void initialize();
            void setTestTimerCallback(void(*func)());
            void updateTestOnTimer();

            void startTestTimer();

            void serviceDataBuffer();

        protected:

            AnalogSubsystem analogSubsystem_;
            CircularBuffer<Sample,DataBufferSize> dataBuffer_;
            Voltammetry voltammetry_;

            IntervalTimer testTimer_;
            static void dummyTimerCallback() {};
            void (*testTimerCallback_)() = dummyTimerCallback;

            uint32_t samplePeriod_ = DefaultSamplePeriod;
            uint32_t sampleModulus_;  
            uint64_t timerCnt_ = 0;

            LowPass currLowPass_;
            BaseTest *test_;
    };


} // namespace ps

#endif
