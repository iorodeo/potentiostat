#include "ps_volt_range.h"
#include "ps_analog_subsystem.h"

namespace ps
{
    uint16_t VoltRangeNew::objCnt_ = 0;
    VoltRangeNew *VoltRangeNew::objPtrArray_[MaxNumberOfVoltRange] = {};


    VoltRangeNew::VoltRangeNew(String name, float minVolt, float maxVolt, VoltGain voltGain, uint16_t maxDac)
          : name_(name), minVolt_(minVolt), maxVolt_(maxVolt), voltGain_(voltGain), maxDac_(maxDac)
    { 

        if (objCnt_< MaxNumberOfVoltRange)
        {
            objInd_ = objCnt_;
            objPtrArray_[objInd_] = this;
            objCnt_++;
        }
    }

    VoltRangeNew::~VoltRangeNew()
    {
        for (int i=objInd_; i<objCnt_-1; i++)
        {
            objPtrArray_[objInd_] = objPtrArray_[objInd_+1];
            objPtrArray_[objInd_] -> objInd_ = objInd_;
        }
        objPtrArray_[objCnt_-1] = nullptr;
        objCnt_--;
    }


    String VoltRangeNew::name()
    {
        return name_;
    }


    float VoltRangeNew::minVolt()
    {
        return minVolt_;
    }


    float VoltRangeNew::maxVolt()
    {
        return maxVolt_;
    }


    uint16_t VoltRangeNew::maxDac()
    {
        return maxDac_;
    }


    VoltGain VoltRangeNew::voltGain()
    {
        return voltGain_;
    }


    String VoltRangeNew::voltGainString()
    {
        return voltGainToString(voltGain_);
    }

    uint16_t VoltRangeNew::voltToDac(float volt)
    {
        uint16_t value = uint16_t(float(maxDac_)/(maxVolt_ - minVolt_)*(maxVolt_ - volt));
        return constrain(value,0,maxDac_);
    }


    float VoltRangeNew::dacToVolt(uint16_t value)
    {
        return maxVolt_ - (float(value)/float(maxDac_))*(maxVolt_ - minVolt_);
    }


    uint16_t VoltRangeNew::numberOfVoltRange()
    {
        return objCnt_;
    }


    VoltRangeNew *VoltRangeNew::getVoltRangeByNumber(uint16_t num)
    {
        VoltRangeNew *voltRangePtr = nullptr;
        if (num < objCnt_)
        {
            voltRangePtr = objPtrArray_[num];
        }
        return voltRangePtr;
    }


    VoltRangeNew *VoltRangeNew::getVoltRangeByName(String name)
    {
        VoltRangeNew *voltRangePtr = nullptr;
        for (int i=0; i< numberOfVoltRange(); i++)
        {
            if (name.equals(objPtrArray_[i]->name()))
            {
                voltRangePtr = objPtrArray_[i];
                break;
            }

        }
        return voltRangePtr;
    }


    // Define VoltRange instances
    VoltRangeNew VoltRangeNew1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDAC);
    VoltRangeNew VoltRangeNew2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDAC);
    VoltRangeNew VoltRangeNew5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDAC);
    VoltRangeNew VoltRangeNew10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDAC);


    // --------------------------------------------------------------------------------------------------------------

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
