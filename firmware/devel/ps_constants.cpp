#include "ps_constants.h"
#include "ps_analog_subsystem.h"

namespace ps
{ 
    // Ranges for output voltage
    // ------------------------------------------------------------------------------------------------------
    const VoltRange VoltRange1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);

    Array<VoltRange,NumVoltRange> createVoltRangeArray()
    {
        Array<VoltRange,NumVoltRange> voltRangeArray;
        voltRangeArray.push_back(VoltRange1V);
        voltRangeArray.push_back(VoltRange2V);
        voltRangeArray.push_back(VoltRange5V);
        voltRangeArray.push_back(VoltRange10V);
        return voltRangeArray;
        
    }
    Array<VoltRange,NumVoltRange> VoltRangeArray = createVoltRangeArray();

    // Ranges for input current
    // ------------------------------------------------------------------------------------------------------
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -100.0, 100.0, CurrGainPathIn3, AnalogSubsystem::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -1000.0, 1000.0, CurrGainPathIn4, AnalogSubsystem::MaxValueAin); 

    Array<CurrRange,NumCurrRange> createCurrRangeArray()
    {
        Array<CurrRange, NumCurrRange> currRangeArray;
        currRangeArray.push_back(CurrRange1uA);
        currRangeArray.push_back(CurrRange10uA);
        currRangeArray.push_back(CurrRange100uA);
        currRangeArray.push_back(CurrRange1000uA);
        return currRangeArray;
    }
    Array<CurrRange, NumCurrRange> CurrRangeArray = createCurrRangeArray();

};
