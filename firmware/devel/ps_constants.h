#ifndef PS_CONSTANTS_H
#define PS_CONSTANTS_H
#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "ps_filter.h"
#include "Array.h"

namespace ps
{

    // Serial command ids
    enum CmdId
    {
        CmdSetVoltOut = 0,
        CmdGetVoltOut = 1,

        CmdGetTIACurr = 2, 
        CmdGetRefElect = 3,

        CmdSetVoltRange = 4,
        CmdGetVoltRange = 5,

        CmdSetCurrRange = 6,
        CmdGetCurrRange = 7,

        CmdSetCyclicTestParam = 8,
        CmdGetCyclicTestParam = 9,
        CmdRunCyclicTest = 10,

        CmdSetConstantTestParam = 11,
        CmdGetConstantTestParam = 12,
        CmdRunConstantTest = 13, 

        CmdSetLinearSweepTestParam = 14,
        CmdGetLinearSweepTestParam = 15,
        CmdRunLinearSweepTest = 16,
        
        CmdSetChronoampTestParam = 17,
        CmdGetChronoampTestParam = 18,
        CmdRunChronoampTest = 19,

        CmdSetMultiStepTestParam = 20,
        CmdGetMultiStepTestParam = 21,
        CmdRunMultiStepTest = 22

    };


    // Data buffer parameters
    const int DataBufferSize = 1000;

    // Ranges for output voltage
    extern const VoltRange VoltRange1V; 
    extern const VoltRange VoltRange2V; 
    extern const VoltRange VoltRange5V; 
    extern const VoltRange VoltRange10V; 

    const int NumVoltRange = 4;
    extern Array<VoltRange,NumVoltRange> VoltRangeArray;

    // Ranges for input current
    extern const CurrRange CurrRange1uA; 
    extern const CurrRange CurrRange10uA; 
    extern const CurrRange CurrRange100uA; 
    extern const CurrRange CurrRange1000uA; 

    const int NumCurrRange = 4;
    extern Array<CurrRange,NumCurrRange> CurrRangeArray;

    // Timer parameters
    extern const uint32_t TestTimerPeriod;      // us
    extern const uint32_t DefaultSamplePeriod;  // us

    // Low pass filter params for current samples
    extern const LowPassParam CurrLowPassParam;
    extern const float LowPassDtSec; 

    // Test parameters
    const int MultiStepMaxSize = 10;

} // namespace ps

#endif
