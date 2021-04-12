#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include <initializer_list>

namespace ps
{ 
    const String FirmwareVersion = String("FW0.0.7");
#if defined HARDWARE_VERSION_0P1
    const String HardwareVersion = String("V0.1");
#elif defined HARDWARE_VERSION_0P2
    const String HardwareVersion = String("V0.2");
#else
#   error "VOLTAGE_VARIANT must be selected"
#endif

    // Serial parameters
    const uint32_t UsbSerialBaudrate = 115200;

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
    const String ChanKey = String("n");
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
    const String MuxEnabledKey = String("muxEnabled");
    const String MuxChannelKey = String("muxChannel");
    const String ConnectedKey = String("connected");
#if defined HARDWARE_VERSION_0P2
    const String ElectAutoConnectKey = String("autoConnect");
#endif

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
    const String SetMuxEnabledCmd = String("setMuxEnabled");
    const String GetMuxEnabledCmd = String("getMuxEnabled");
    const String SetEnabledMuxChanCmd = String("setEnabledMuxChannels");
    const String GetEnabledMuxChanCmd = String("getEnabledMuxChannels");
    const String GetMuxTestNamesCmd = String("getMuxTestNames");
    const String SetMuxRefElectConnCmd = String("setMuxRefElectConnected");
    const String GetMuxRefElectConnCmd = String("getMuxRefElectConnected");
    const String SetMuxCtrElectConnCmd = String("setMuxCtrElectConnected");
    const String GetMuxCtrElectConnCmd = String("getMuxCtrElectConnected");
    const String SetMuxWrkElectConnCmd = String("setMuxWrkElectConnected");
    const String GetMuxWrkElectConnCmd = String("getMuxWrkElectConnected");
    const String DisconnAllMuxElectCmd = String("disconnectAllMuxElect");
#if defined HARDWARE_VERSION_0P2
    const String SetRefElectConnCmd = String("setRefElectConnected");
    const String GetRefElectConnCmd = String("getRefElectConnected");
    const String SetCtrElectConnCmd = String("setCtrElectConnected");
    const String GetCtrElectConnCmd = String("getCtrElectConnected");
    const String SetWrkElectConnCmd = String("setWrkElectConnected");
    const String GetWrkElectConnCmd = String("getWrkElectConnected");
    const String SetAllElectConnCmd = String("setAllElectConnected");
    const String GetAllElectConnCmd = String("getAllElectConnected");
    const String SetElectAutoConnCmd = String("setElectAutoConnect");
    const String GetElectAutoConnCmd = String("getElectAutoConnect");
    const String SetRefElectVoltRangeCmd = String("setRefElectVoltRange");
    const String GetRefElectVoltRangeCmd = String("getRefElectVoltRange");
    const String GetHardwareVersionCmd = String("getHardwareVersion");
#endif


    // Ranges for output voltage
#if defined VOLTAGE_VARIANT_10V
    const String VoltageVariant = String("10V");
    const VoltRangeDac VoltRangeDac1V(String("1V"), -1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac2V(String("2V"), -2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac5V(String("5V"), -5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);
    VoltRangeDac DacArrayTmp[NumVoltRangeDac] = {VoltRangeDac1V, VoltRangeDac2V, VoltRangeDac5V, VoltRangeDac10V};
#elif defined VOLTAGE_VARIANT_AD8250
    const String VoltageVariant = String("AD8250");
    const VoltRangeDac VoltRangeDac1V(String("1V"), -1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac2V(String("2V"), -2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac5V(String("5V"), -5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);
    VoltRangeDac DacArrayTmp[NumVoltRangeDac] = {VoltRangeDac1V, VoltRangeDac2V, VoltRangeDac5V, VoltRangeDac10V};
#elif defined VOLTAGE_VARIANT_AD8251
    const String VoltageVariant = String("AD8251");
    const VoltRangeDac VoltRangeDac1V(String("1V"), -1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac2V(String("2V"), -2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac4V(String("4V"), -4.0, 4.0, VoltGain4X, AnalogSubsystem::MaxValueDac);
    const VoltRangeDac VoltRangeDac8V(String("8V"), -8.0, 8.0, VoltGain8X, AnalogSubsystem::MaxValueDac);
    VoltRangeDac DacArrayTmp[NumVoltRangeDac] = {VoltRangeDac1V, VoltRangeDac2V, VoltRangeDac4V, VoltRangeDac8V};
#else
#   error "VOLTAGE_VARIANT must be selected"
#endif 
    Array<VoltRangeDac,NumVoltRangeDac> VoltRangeDacArray(DacArrayTmp);
    const float SignDac = -1.0; 

    // Range for reference electrode analog input
    const VoltRangeAdc VoltRangeAdc1V(String("1V"), -1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueAin);
    const VoltRangeAdc VoltRangeAdc2V(String("2V"), -2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueAin);
    const VoltRangeAdc VoltRangeAdc5V(String("5V"), -5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueAin);
    const VoltRangeAdc VoltRangeAdc10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueAin);
    VoltRangeAdc AdcArrayTmp[NumVoltRangeAdc] = {VoltRangeAdc1V, VoltRangeAdc2V, VoltRangeAdc5V, VoltRangeAdc10V};
    Array<VoltRangeAdc,NumVoltRangeAdc> VoltRangeAdcArray(AdcArrayTmp);
    const float SignAdc = 1.0; 

    // Ranges for input current
#if defined CURRENT_VARIANT_NANO_AMP
    const String CurrentVariant = String("nanoAmp");
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange60nA("60nA", -0.06, 0.06, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100nA("100nA", -0.1, 0.1, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange1uA, CurrRange10uA, CurrRange60nA, CurrRange100nA};
#elif defined CURRENT_VARIANT_MILL_AMP
    const String CurrentVariant = String("milliAmp");
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange12000uA("12000uA", -12024.0, 12024.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange24000uA("24000uA", -24048.0, 24048.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange100uA, CurrRange1000uA, CurrRange12000uA, CurrRange24000uA};
#elif defined CURRENT_VARIANT_MICRO_AMP
    const String CurrentVariant = String("microAmp");
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 
    CurrRange currRangeArrayTmp[NumCurrRange] = {CurrRange1uA, CurrRange10uA, CurrRange100uA, CurrRange1000uA};
#else
#   error "CURRENT_VARIANT must be selected"
#endif
    const String HardwareVariant = VoltageVariant + String("_") + CurrentVariant + HardwareVersion;
    Array<CurrRange,NumCurrRange>  CurrRangeArray(currRangeArrayTmp);

#if defined HARDWARE_VERSION_0P1
    const float SignCurr =  1.0;
#elif defined HARDWARE_VERSION_0P2
    const float SignCurr = -1.0;
#else
#   error "HARDWARE_VERSION must be specified"
#endif

    // Timer parameters
    const uint32_t TestTimerPeriod = 200;                // us
    const uint32_t DefaultSamplePeriod = 10000;          // us
    extern const uint32_t MinimumSamplePeriod = 1000;    // us
    extern const uint32_t MaximumSamplePeriod = 1000000; // us

    // Low pass filter params for current samples
    const LowPassParam CurrLowPassParam = {200.0, 0.0, 2}; // cutoff freq (Hz), initial value, order

} // namespace ps
