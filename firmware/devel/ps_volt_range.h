#ifndef PS_VOLT_RANGE_H
#define PS_VOLT_RANGE_H
#include <Arduino.h>

// old
#include "ps_gains.h"

namespace ps
{

    class VoltRangeNew
    {

        public:

            static const uint16_t MaxNumberOfVoltRange = 4;

            VoltRangeNew(String name, float minVolt, float maxVolt, VoltGain voltGain, uint16_t maxDac);

            ~VoltRangeNew();

            String name();
            float minVolt();
            float maxVolt();
            uint16_t maxDac();
            VoltGain voltGain();
            String voltGainString();

            uint16_t voltToDac(float volt);
            float dacToVolt(uint16_t value);

            static uint16_t numberOfVoltRange();
            static VoltRangeNew *getVoltRangeByNumber(uint16_t num);
            static VoltRangeNew *getVoltRangeByName(String name);

        protected:

            static uint16_t objCnt_;
            static VoltRangeNew *objPtrArray_[MaxNumberOfVoltRange];
            uint16_t objInd_;

            String name_;
            float minVolt_;
            float maxVolt_;
            VoltGain voltGain_;
            uint16_t maxDac_;

    };

    extern VoltRangeNew VoltRangeNew1V; 
    extern VoltRangeNew VoltRangeNew2V; 
    extern VoltRangeNew VoltRangeNew5V; 
    extern VoltRangeNew VoltRangeNew10V; 


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
