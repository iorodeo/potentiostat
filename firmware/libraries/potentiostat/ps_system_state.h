#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H

#include <Arduino.h>
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

#include "third-party/ArduinoJson/ArduinoJson.h"

namespace ps
{

    class SystemState
    {

        public:

            SystemState();
            void initialize();

            void processMessages();
            void updateMessageData();
            void serviceDataBuffer();

            ReturnStatus onCommandRunTest(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandStopTest(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetVolt(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetVolt(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetCurr(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetRefVolt(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetTestParam(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetTestParam(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetCurrRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetCurrRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetDeviceId(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetDeviceId(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetSamplePeriod(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetSamplePeriod(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetTestDoneTime(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetTestNames(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetVersion(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetVariant(JsonObject &jsonMsg, JsonObject &jsonDat);

            void startTest();
            void stopTest();

            void setSamplePeriod(uint32_t samplePeriod);
            uint32_t getSamplePeriod();

            void setTestTimerCallback(void(*func)());
            void updateTestOnTimer();


        protected:

            volatile bool testInProgress_;
            volatile bool lastSampleFlag_;

            AnalogSubsystem analogSubsystem_;

            MessageReceiver messageReceiver_;
            MessageParser messageParser_;
            MessageSender messageSender_;

            CommandTable<SystemState,CommandTableMaxSize> commandTable_;
            StaticJsonBuffer<JsonMessageBufferSize> commandRespJsonBuffer_;

            CircularBuffer<Sample,DataBufferSize> dataBuffer_;
            Voltammetry voltammetry_;

            IntervalTimer testTimer_;
            void (*testTimerCallback_)() = dummyTimerCallback;

            uint32_t samplePeriod_; 
            uint32_t sampleModulus_;  
            uint64_t timerCnt_;

            LowPass currLowPass_;
            BaseTest *test_;

            static void dummyTimerCallback() {};
            void updateSampleModulus();
    };


} // namespace ps

#endif
