#ifndef PS_CONSTANTS_H
#define PS_CONSTANTS_H
#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "ps_filter.h"
#include "Array.h"

namespace ps
{
    // Buffer parameters
    const uint32_t DataBufferSize = 1000;
    const uint32_t SerialBufferSize = 1000;
    const uint32_t JsonBufferSize = 1000;

    // Serial parameters
    extern const uint32_t UsbSerialBaudrate;

    // Ranges for output voltage
    extern const VoltRange VoltRange1V; 
    extern const VoltRange VoltRange2V; 
    extern const VoltRange VoltRange5V; 
    extern const VoltRange VoltRange10V; 

    const uint8_t NumVoltRange = 4;
    extern Array<VoltRange,NumVoltRange> VoltRangeArray;

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

    // Low pass filter params for current samples
    extern const LowPassParam CurrLowPassParam;
    extern const float LowPassDtSec; 

    // Test parameters
    const uint8_t MultiStepMaxSize = 10;

} // namespace ps

#endif
