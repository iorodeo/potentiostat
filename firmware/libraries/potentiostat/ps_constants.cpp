#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include <initializer_list>

namespace ps
{ 
    const String FirmwareVersion = String("0.0.4");

    // Serial parameters
    const uint32_t UsbSerialBaudrate = 115200;
    const uint32_t JsonFloatDecimals = 5;

    // Device ID EEPROM address
    extern const uint32_t EEPROM_DeviceIdAddress = 0;

    // Json message keys 
    const String CommandKey = String("command");
    const String ResponseKey = String("response");
    const String MessageKey = String("message");
    const String SuccessKey = String("success");
    const String TimeKey = String("t");
    const String VoltKey = String("v");
    const String CurrKey = String("i");
    const String RefVoltKey = String("r");
    const String ParamKey = String("param");
    const String VoltRangeKey = String("voltRange");
    const String CurrRangeKey = String("currRange");
    const String QuietValueKey = String("quietValue"); 
    const String QuietTimeKey = String("quietTime");
    const String DurationKey = String("duration");
    const String ValueKey = String("value");
    const String StartValueKey = String("startValue");
    const String FinalValueKey = String("finalValue");
    const String StepValueKey = String("stepValue");
    const String AmplitudeKey = String("amplitude");
    const String OffsetKey = String("offset");
    const String PeriodKey = String("period");
    const String NumCyclesKey = String("numCycles");
    const String ShiftKey = String("shift");
    const String WindowKey = String("window");
    const String DeviceIdKey = String("deviceId");
    const String SamplePeriodKey = String("samplePeriod");
    const String TestDoneTimeKey = String("testDoneTime");
    const String StepArrayKey = String("step");
    const String TestNameArrayKey = String("testNames");
    const String VersionKey = String("version");
    const String VariantKey = String("variant");

    // Json command strings
    const String RunTestCmd = String("runTest");
    const String StopTestCmd = String("stopTest");
    const String GetVoltCmd = String("getVolt");
    const String SetVoltCmd = String("setVolt");
    const String GetCurrCmd = String("getCurr");
    const String GetRefVoltCmd = String("getRefVolt");
    const String SetParamCmd = String("setParam");
    const String GetParamCmd = String("getParam");
    const String SetVoltRangeCmd = String("setVoltRange");
    const String GetVoltRangeCmd = String("getVoltRange");
    const String SetCurrRangeCmd = String("setCurrRange");
    const String GetCurrRangeCmd = String("getCurrRange");
    const String SetDeviceIdCmd = String("setDeviceId");
    const String GetDeviceIdCmd = String("getDeviceId");
    const String SetSamplePeriodCmd = String("setSamplePeriod");
    const String GetSamplePeriodCmd = String("getSamplePeriod");
    const String GetTestDoneTimeCmd = String("getTestDoneTime");
    const String GetTestNamesCmd = String("getTestNames");
    const String GetVersionCmd = String("getVersion");
    const String GetVariantCmd = String("getVariant");

    // Ranges for output voltage
    const VoltRange VoltRange1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);

    VoltRange voltRangeArrayTmp[NumVoltRange] = {VoltRange1V, VoltRange2V, VoltRange5V, VoltRange10V};
    Array<VoltRange,NumVoltRange> VoltRangeArray(voltRangeArrayTmp);
    const float SignDac = -1.0; 

    // Range for reference electrode analog input
    const VoltRange VoltRangeAin10V(String("Ain10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueAin);

    // Ranges for input current
#if defined HARDWARE_VARIANT_NANO_AMP
    const String HardwareVariant = String("nanoAmpV0.1");
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange60nA("60nA", -0.06, 0.06, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100nA("100nA", -0.1, 0.1, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange1uA, CurrRange10uA, CurrRange60nA, CurrRange100nA};
#elif defined HARDWARE_VARIANT_MILL_AMP
    const String HardwareVariant = String("milliAmpV0.1");
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange12000uA("12000uA", -12024.0, 12024.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange24000uA("24000uA", -24048.0, 24048.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange100uA, CurrRange1000uA, CurrRange12000uA, CurrRange24000uA};
#else
    const String HardwareVariant = String("microAmpV0.1");
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange1uA, CurrRange10uA, CurrRange100uA, CurrRange1000uA};
#endif
    Array<CurrRange,NumCurrRange>  CurrRangeArray(currRangeArrayTmp);

    // Timer parameters
    const uint32_t TestTimerPeriod = 200;                // us
    const uint32_t DefaultSamplePeriod = 10000;          // us
    extern const uint32_t MinimumSamplePeriod = 1000;    // us
    extern const uint32_t MaximumSamplePeriod = 1000000; // us

    // Low pass filter params for current samples
    const LowPassParam CurrLowPassParam = {200.0, 0.0, 2}; // cutoff freq (Hz), initial value, order
    const float LowPassDtSec = 1.0e-6*TestTimerPeriod;    // (s)

} // namespace ps
