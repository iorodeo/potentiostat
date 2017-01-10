#ifndef PS_VOLT_RANGE_H
#define PS_VOLT_RANGE_H
#include <Arduino.h>
#include "ps_gains.h"

namespace ps
{

    // TO DO .. modify so that VoltRange is a clas.

    enum VoltRange
    {
        VoltRange1V  = 0,
        VoltRange2V  = 1,
        VoltRange5V  = 2,
        VoltRange10V = 3,
        NumVoltRange = 4
    };

    const String voltRangeStringArray[NumVoltRange] = 
    {
        String("1V"),
        String("2V"),
        String("5V"),
        String("10V")
    };

    const VoltGain VoltRangeToGainMap[NumVoltRange] =
    {
        VoltGain1X, // VoltRange1V
        VoltGain2X, // VoltRange2V
        VoltGain5X, // VoltRange5V
        VoltGain10X // VoltRagne10V
    };

    const VoltRange VoltGainToRangeMap[NumVoltGain] =
    {
        VoltRange1V,  // VoltGain1X
        VoltRange2V,  // VoltGain2x
        VoltRange5V,  // VoltGain5X
        VoltRange10V  // VoltGain10X
    };

    const float VoltRangeMaxValueArray[NumVoltRange] = { 1.0,  2.0,  5.0,  10.0};
    const float VoltRangeMinValueArray[NumVoltRange] = {-1.0, -2.0, -5.0, -10.0};

    String voltRangeToString(VoltRange value);
    VoltGain voltRangeToGain(VoltRange value);
    VoltRange voltGainToRange(VoltGain value);
    float voltRangeMaxValue(VoltRange voltRange);
    float voltRangeMinValue(VoltRange voltRange);
    uint16_t voltToDAC(float valueVolt, VoltRange voltRange, uint16_t maxValueDAC);
    uint16_t DACToVolt(uint16_t valueDAC, VoltRange voltRange, uint16_t maxValueDAC);

}

#endif
