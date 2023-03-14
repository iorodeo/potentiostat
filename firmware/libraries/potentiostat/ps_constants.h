#ifndef PS_CONSTANTS_H
#define PS_CONSTANTS_H

#include "ps_hardware_defs.h"
#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "ps_filter.h"
#include "Array.h"
//#if defined DEVBOARD_ITSY_BITSY
//    #include "FlashStorage.h"
//#endif


namespace ps
{
    extern const String FirmwareVersion;
    extern const String HardwareVariant;
#if defined HARDWARE_VERSION_0P2
    extern const String HardwareVersion;
#endif

    // Command tabe parameters
    const uint32_t CommandTableMaxSize = 50;
    
    // Buffer parameters
    const uint32_t DataBufferSize = 1000;
    const uint32_t SerialBufferSize = 2000; 
    const uint32_t JsonMessageBufferSize = 4000;
    const uint32_t JsonTestDataBufferSize = 4000;

#if defined DEVBOARD_TEENSY
    // Device ID EEPROM address
    extern const uint32_t EEPROM_DeviceIdAddress;
#endif

    // Serial parameters
    extern const uint32_t UsbSerialBaudrate;

    // Json message keys 
    extern const String CommandKey;
    extern const String ResponseKey;
    extern const String MessageKey;
    extern const String SuccessKey;
    extern const String TimeKey;
    extern const String VoltKey;
    extern const String CurrKey;
    extern const String ChanKey;
    extern const String RefVoltKey;
    extern const String ParamKey;
    extern const String VoltRangeKey;
    extern const String CurrRangeKey;
    extern const String QuietValueKey; 
    extern const String QuietTimeKey;
    extern const String DurationKey;
    extern const String ValueKey;
    extern const String StartValueKey;
    extern const String FinalValueKey;
    extern const String StepValueKey;
    extern const String AmplitudeKey;
    extern const String OffsetKey;
    extern const String PeriodKey;
    extern const String NumCyclesKey;
    extern const String ShiftKey;
    extern const String WindowKey;
    extern const String DeviceIdKey;
    extern const String SamplePeriodKey;
    extern const String TestDoneTimeKey;
    extern const String StepArrayKey;
    extern const String TestNameArrayKey;
    extern const String VersionKey;
    extern const String VariantKey;
    extern const String MuxEnabledKey;
    extern const String MuxChannelKey;
    extern const String ConnectedKey;
#if defined HARDWARE_VERSION_0P2
    extern const String ElectAutoConnectKey;
#endif


    // Json command strings
    extern const String RunTestCmd;
    extern const String StopTestCmd;
    extern const String GetVoltCmd;
    extern const String SetVoltCmd;
    extern const String GetCurrCmd;
    extern const String GetRefVoltCmd;
    extern const String SetParamCmd;
    extern const String GetParamCmd;
    extern const String SetVoltRangeCmd;
    extern const String GetVoltRangeCmd;
    extern const String SetCurrRangeCmd;
    extern const String GetCurrRangeCmd;
    extern const String SetDeviceIdCmd;
    extern const String GetDeviceIdCmd;
    extern const String SetSamplePeriodCmd;
    extern const String GetSamplePeriodCmd;
    extern const String GetTestDoneTimeCmd;
    extern const String GetTestNamesCmd;
    extern const String GetVersionCmd;
    extern const String GetVariantCmd;
    extern const String SetMuxEnabledCmd;
    extern const String GetMuxEnabledCmd;
    extern const String SetEnabledMuxChanCmd;
    extern const String GetEnabledMuxChanCmd;
    extern const String GetMuxTestNamesCmd;
    extern const String SetMuxRefElectConnCmd;
    extern const String GetMuxRefElectConnCmd;
    extern const String SetMuxCtrElectConnCmd;
    extern const String GetMuxCtrElectConnCmd;
    extern const String SetMuxWrkElectConnCmd;
    extern const String GetMuxWrkElectConnCmd;
    extern const String DisconnAllMuxElectCmd;
#if defined HARDWARE_VERSION_0P2
    extern const String SetRefElectConnCmd;
    extern const String GetRefElectConnCmd;
    extern const String SetCtrElectConnCmd;
    extern const String GetCtrElectConnCmd;
    extern const String SetWrkElectConnCmd;
    extern const String GetWrkElectConnCmd;
    extern const String SetAllElectConnCmd;
    extern const String GetAllElectConnCmd;
    extern const String SetElectAutoConnCmd;
    extern const String GetElectAutoConnCmd;
    extern const String SetRefElectVoltRangeCmd;
    extern const String GetRefElectVoltRangeCmd;
    extern const String GetHardwareVersionCmd; 
#endif

    // Ranges for output voltage
    extern const VoltRangeDac VoltRangeDac1V; 
    extern const VoltRangeDac VoltRangeDac2V; 
    extern const VoltRangeDac VoltRangeDac5V; 
    extern const VoltRangeDac VoltRangeDac10V; 

    const uint8_t NumVoltRangeDac = 4;
    extern Array<VoltRangeDac,NumVoltRangeDac> VoltRangeDacArray;
    extern const float SignDac; 

    // Range for reference electrode analog input
    extern const VoltRangeAdc VoltRangeAdc1V;
    extern const VoltRangeAdc VoltRangeAdc2V;
    extern const VoltRangeAdc VoltRangeAdc5V;
    extern const VoltRangeAdc VoltRangeAdc10V;

    const uint8_t NumVoltRangeAdc = 4;
    extern Array<VoltRangeAdc,NumVoltRangeAdc> VoltRangeAdcArray;
    extern const float SignAdc; 

    // Ranges for input current
    extern const CurrRange CurrRange1uA; 
    extern const CurrRange CurrRange10uA; 
    extern const CurrRange CurrRange100uA; 
    extern const CurrRange CurrRange1000uA; 

    const uint8_t NumCurrRange = 4;
    extern Array<CurrRange,NumCurrRange> CurrRangeArray;
    extern const float SignCurr;

    // Timer parameters
    extern const uint32_t TestTimerPeriod;      // us
    extern const uint32_t DefaultSamplePeriod;  // us
    extern const uint32_t MinimumSamplePeriod;  // us
    extern const uint32_t MaximumSamplePeriod;  // us

    // Low pass filter params for current samples
    extern const LowPassParam CurrLowPassParam;

    // Test parameters
    const uint32_t AvailableTestsMaxSize = 20;
    const uint32_t MultiStepMaxSize = 50;

    enum SampleMethod {SampleGeneric, SampleCustom};

    // Multiplexer Parameters
#if defined MUX_CAPABLE
    const uint8_t NumMuxChan = 7;
    const uint8_t NumMuxPin = 16;
#else
    const uint8_t NumMuxChan = 1;
    const uint8_t NumMuxPin = 1;
#endif

} // namespace ps

#endif
