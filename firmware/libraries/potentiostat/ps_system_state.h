#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H

#include <Arduino.h>
#include "ps_hardware_defs.h"
#include "ps_constants.h"
#include "ps_return_status.h"
#include "ps_analog_subsystem.h"
#include "ps_electrode_switch.h"
#include "ps_message_receiver.h"
#include "ps_message_sender.h"
#include "ps_message_parser.h"
#include "ps_command_table.h"
#include "ps_circular_buffer.h"
#include "ps_voltammetry.h"
#include "ps_sample.h"
#include "ps_filter.h"
#include "ps_multiplexer.h"
#include "third-party/Array/Array.h"
#define ARDUINOJSON_USE_DOUBLE 0
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
            ReturnStatus onCommandSetMuxEnabled(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetMuxEnabled(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetEnabledMuxChan(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetEnabledMuxChan(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetMuxTestNames(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetMuxRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetMuxRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetMuxCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetMuxCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetMuxWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetMuxWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandDisconnAllMuxElect(JsonObject &jsonMsg, JsonObject &jsonDat);
#if defined HARDWARE_VERSION_0P2
            ReturnStatus onCommandSetRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetRefElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetCtrElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetWrkElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetAllElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetAllElectConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetElectAutoConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetElectAutoConn(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandSetRefElectVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetRefElectVoltRange(JsonObject &jsonMsg, JsonObject &jsonDat);
            ReturnStatus onCommandGetHardwareVersion(JsonObject &jsonMsg, JsonObject &jsonDat); 
#endif
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
            Multiplexer multiplexer_;

#if defined HARDWARE_VERSION_0P2
            ElectrodeSwitch electrodeSwitch_;
            bool electrodeAutoConnect_;
#endif
            MessageReceiver messageReceiver_;
            MessageParser messageParser_;
            MessageSender messageSender_;

            CommandTable<SystemState,CommandTableMaxSize> commandTable_;

            CircularBuffer<Sample,DataBufferSize> dataBuffer_;
            Voltammetry voltammetry_;

            IntervalTimer testTimer_;
            void (*testTimerCallback_)() = dummyTimerCallback;
            volatile uint64_t timerCnt_;
            uint32_t samplePeriod_; 
            uint32_t sampleModulus_;  

            Array<LowPass,NumMuxChan> currLowPass_;
            float lowPassDtSec_;
            BaseTest *test_;

            static void dummyTimerCallback() {};
            void updateSampleModulus();
    };


} // namespace ps

#endif
