#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include <initializer_list>

namespace ps
{ 
    // Serial parameters
    extern const uint32_t UsbSerialBaudrate = 115200;

    // Ranges for output voltage
    const VoltRange VoltRange1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);

    VoltRange voltRangeArrayTmp[NumVoltRange] = {VoltRange1V, VoltRange2V, VoltRange5V, VoltRange10V};
    Array<VoltRange,NumVoltRange> VoltRangeArray(voltRangeArrayTmp);

    // Ranges for input current
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 

    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange1uA,CurrRange10uA, CurrRange10uA, CurrRange100uA};
    Array<CurrRange,NumCurrRange>  CurrRangeArray(currRangeArrayTmp);

    // Timer parameters
    const uint32_t TestTimerPeriod = 100;         // us
    const uint32_t DefaultSamplePeriod = 10000;   // us

    // Low pass filter params for current samples
    const LowPassParam CurrLowPassParam = {50.0, 0.0, 2}; // cutoff freq (Hz), initial value, order
    const float LowPassDtSec = 1.0e-6*TestTimerPeriod;    // (s)



} // namespace ps
