#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H
#include <Arduino.h>
#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include "ps_voltammetry.h"
#include "ps_circular_buffer.h"
#include "ps_test_data.h"

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

        protected:

            AnalogSubsystem analogSubsystem_;
            CircularBuffer<TestData,DataBufferSize> dataBuffer_;
            Voltammetry voltammetry_;

            IntervalTimer testTimer_;
            static void dummyTimerCallback() {};
            void (*testTimerCallback_)() = dummyTimerCallback;

            double dt_ = (TestTimerPeriod*1.0e-6);
            double t_ = 0.0;

            BaseTest *test_;
    };


} // namespace ps

#endif
