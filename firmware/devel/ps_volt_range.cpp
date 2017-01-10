#include "ps_volt_range.h"

namespace ps
{
    String voltRangeToString(VoltRange value)
    {
        String voltRangeString("");
        if (value < NumVoltRange)
        {
            voltRangeString = voltRangeStringArray[value];
        }
        return voltRangeString;
    }


    VoltGain voltRangeToGain(VoltRange value)
    {
        VoltGain voltGain = VoltGain(0);
        if (value < NumVoltRange)
        {
            voltGain = VoltRangeToGainMap[value];
        }
        return voltGain;
    }


    VoltRange voltGainToRange(VoltGain value)
    {
        VoltRange voltRange = VoltRange(0);
        if (value < NumVoltGain)
        {
            voltRange = VoltGainToRangeMap[value];
        }
        return voltRange;
    }


    float voltRangeMaxValue(VoltRange voltRange)
    {
        float maxValue = 1.0;
        if (voltRange < NumVoltRange)
        {
            maxValue = VoltRangeMaxValueArray[voltRange];
        }
        return maxValue;
    }


    float voltRangeMinValue(VoltRange voltRange)
    {
        float minValue;
        if (voltRange < NumVoltRange)
        {
            minValue = VoltRangeMinValueArray[voltRange];
        }
        return minValue;
    }


    uint16_t voltToDAC(float valueVolt, VoltRange voltRange, uint16_t maxValueDAC)
    {
        float minValue = voltRangeMinValue(voltRange);
        float maxValue = voltRangeMaxValue(voltRange);
        uint16_t valueDAC = uint16_t(float(maxValueDAC)/(maxValue - minValue)*(maxValue - valueVolt));
        valueDAC = constrain(valueDAC,0,maxValueDAC);
        return valueDAC;
    }


    uint16_t DACToVolt(uint16_t valueDAC, VoltRange voltRange, uint16_t maxValueDAC)
    {
        float minValue = voltRangeMinValue(voltRange);
        float maxValue = voltRangeMaxValue(voltRange);
        float valueVolt = maxValue  - (float(valueDAC)/float(maxValueDAC))*(maxValue - minValue);
        return valueVolt;
    }

}
