#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include <initializer_list>

namespace ps
{ 
    // Serial parameters
    const uint32_t UsbSerialBaudrate = 115200;
    const uint32_t JsonFloatDecimals = 5;

    // Json message keys 
    const String CommandKey = String("command");
    const String ResponseKey = String("response");
    const String MessageKey = String("message");
    const String SuccessKey = String("success");

    const String RunTestKey = String("runTest");
    const String StopTestKey = String("stopTest");
    const String SetVoltKey = String("setVolt");
    const String GetCurrKey = String("getCurr");
    const String SetParamKey = String("setParam");
    const String GetParamKey = String("getParam");
    const String SetVoltRangeKey = String("setVoltRange");
    const String GetVoltRangeKey = String("getVoltRange");
    const String SetCurrRangeKey = String("setCurrRange");
    const String GetCurrRangeKey = String("getCurrRange");

    const String CurrKey = String("i");
    const String VoltKey = String("v");
    const String TimeKey = String("t");

    const String ParamKey = String("param");
    const String QuietValueKey = String("quietValue"); 
    const String QuietTimeKey = String("quietTime");

    const String DurationKey = String("duration");
    const String ValueKey = String("value");

    const String StartValueKey = String("startValue");
    const String FinalValueKey = String("finalValue");

    const String AmplitudeKey = String("amplitude");
    const String OffsetKey = String("offset");
    const String PeriodKey = String("period");
    const String NumCyclesKey = String("numCycles");
    const String ShiftKey = String("shift");

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
    const uint32_t TestTimerPeriod = 200;         // us
    const uint32_t DefaultSamplePeriod = 10000;   // us

    // Low pass filter params for current samples
    const LowPassParam CurrLowPassParam = {50.0, 0.0, 2}; // cutoff freq (Hz), initial value, order
    const float LowPassDtSec = 1.0e-6*TestTimerPeriod;    // (s)



} // namespace ps
