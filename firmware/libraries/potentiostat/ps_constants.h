#ifndef PS_CONSTANTS_H
#define PS_CONSTANTS_H

#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "ps_filter.h"

#include "third-party/Array/Array.h"

//#define HARDWARE_VARIANT_NANO_AMP
//#define HARDWARE_VARIANT_MILL_AMP

namespace ps
{
    extern const String FirmwareVersion;
    extern const String HardwareVariant;

    // Command tabe parameters
    const uint32_t CommandTableMaxSize = 25;
    
    // Buffer parameters
    const uint32_t DataBufferSize = 1000;
    const uint32_t SerialBufferSize = 1000;
    const uint32_t JsonMessageBufferSize = 5000;
    const uint32_t JsonTestDataBufferSize = 5000;

    // Device ID EEPROM address
    extern const uint32_t EEPROM_DeviceIdAddress;

    // Serial parameters
    extern const uint32_t UsbSerialBaudrate;
    extern const uint32_t JsonFloatDecimals;

    // Json message keys 
    extern const String CommandKey;
    extern const String ResponseKey;
    extern const String MessageKey;
    extern const String SuccessKey;
    extern const String TimeKey;
    extern const String VoltKey;
    extern const String CurrKey;
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

    // Ranges for output voltage
    extern const VoltRange VoltRange1V; 
    extern const VoltRange VoltRange2V; 
    extern const VoltRange VoltRange5V; 
    extern const VoltRange VoltRange10V; 

    // Range for reference electrode analog input
    extern const VoltRange VoltRangeAin10V;

    const uint8_t NumVoltRange = 4;
    extern Array<VoltRange,NumVoltRange> VoltRangeArray;
    extern const float SignDac; 

    // Ranges for input current
    extern const CurrRange CurrRange1uA; 
    extern const CurrRange CurrRange10uA; 
    extern const CurrRange CurrRange100uA; 
    extern const CurrRange CurrRange1000uA; 

    const uint8_t NumCurrRange = 4;
    extern Array<CurrRange,NumCurrRange> CurrRangeArray;

    // Timer parameters
    extern const uint32_t TestTimerPeriod;      // us
    extern const uint32_t DefaultSamplePeriod;  // us
    extern const uint32_t MinimumSamplePeriod;  // us
    extern const uint32_t MaximumSamplePeriod;  // us

    // Low pass filter params for current samples
    extern const LowPassParam CurrLowPassParam;
    extern const float LowPassDtSec; 

    // Test parameters
    const uint32_t AvailableTestsMaxSize = 20;
    const uint32_t MultiStepMaxSize = 50;

    enum SampleMethod {SampleGeneric, SampleCustom};


} // namespace ps

#endif
