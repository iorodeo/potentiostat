#include "ps_volt_range.h"
#include "ps_analog_subsystem.h"

namespace ps
{

    // VoltRange methods
    // --------------------------------------------------------------------------------------------

    VoltRange::VoltRange(String name, float minVolt, float maxVolt, VoltGain voltGain, uint16_t maxDac)
          : name_(name), minVolt_(minVolt), maxVolt_(maxVolt), voltGain_(voltGain), maxDac_(maxDac)
    { }

    String VoltRange::name() const
    {
        return name_;
    }


    float VoltRange::minVolt() const
    {
        return minVolt_;
    }


    float VoltRange::maxVolt() const
    {
        return maxVolt_;
    }


    uint16_t VoltRange::maxDac() const
    {
        return maxDac_;
    }


    VoltGain VoltRange::voltGain() const
    {
        return voltGain_;
    }


    String VoltRange::voltGainString() const
    {
        return voltGainToString(voltGain_);
    }

    uint16_t VoltRange::voltToDac(float volt) const
    {
        uint16_t value = uint16_t(float(maxDac_)/(maxVolt_ - minVolt_)*(maxVolt_ - volt));
        return constrain(value,0,maxDac_);
    }


    float VoltRange::dacToVolt(uint16_t value) const
    {
        return maxVolt_ - (float(value)/float(maxDac_))*(maxVolt_ - minVolt_);
    }


    // Define VoltRange instances
    // --------------------------------------------------------------------------------------------
    const VoltRange VoltRange1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystemHW::MaxValueDac);
    const VoltRange VoltRange2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystemHW::MaxValueDac);
    const VoltRange VoltRange5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystemHW::MaxValueDac);
    const VoltRange VoltRange10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystemHW::MaxValueDac);


    // VoltRangeVector methods
    // ----------------------------------------------------------------------------------------------

    VoltRangeFixedVector::VoltRangeFixedVector()
    {
        set(0,VoltRange1V);
        set(1,VoltRange2V);
        set(2,VoltRange5V);
        set(3,VoltRange10V);
    }

    // VoltageRangeFixedVector instance
    // --------------------------------------------------------------------------------------------
    VoltRangeFixedVector VoltRangeVector;

} // namespace ps
