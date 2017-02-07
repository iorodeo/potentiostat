#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H
#include <Arduino.h>
#include "ArduinoJson.h"
#include "ps_constants.h"
#include "ps_return_status.h"
#include "ps_analog_subsystem.h"
#include "ps_message_receiver.h"
#include "ps_message_sender.h"
#include "ps_message_parser.h"
#include "ps_command_table.h"
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

            void processMessages();
            void updateMessageData();

            void startTestTimer();
            void serviceDataBuffer();

            ReturnStatus runTest(JsonObject &jsonRoot);
            ReturnStatus stopTest(JsonObject &jsonRoot);

            ReturnStatus setVolt(JsonObject &jsonRoot);
            ReturnStatus getCurr(JsonObject &jsonRoot);

            ReturnStatus setTestParam(JsonObject &jsonRoot);
            ReturnStatus getTestParam(JsonObject &jsonRoot);

            ReturnStatus setVoltRange(JsonObject &jsonRoot);
            ReturnStatus getVoltRange(JsonObject &jsonRoot);

            ReturnStatus setCurrRange(JsonObject &jsonRoot);
            ReturnStatus getCurrRange(JsonObject &jsonRoot);

            void debug();

        protected:

            AnalogSubsystem analogSubsystem_;

            MessageReceiver messageReceiver_;
            MessageParser messageParser_;
            MessageSender messageSender_;

            CommandTable<SystemState,10> commandTable_;

            CircularBuffer<Sample,DataBufferSize> dataBuffer_;
            Voltammetry voltammetry_;

            IntervalTimer testTimer_;
            void (*testTimerCallback_)() = dummyTimerCallback;

            uint32_t samplePeriod_ = DefaultSamplePeriod;
            uint32_t sampleModulus_;  
            uint64_t timerCnt_;

            LowPass currLowPass_;
            BaseTest *test_;

            static void dummyTimerCallback() {};
            void updateSampleModulus();
    };


} // namespace ps

#endif
