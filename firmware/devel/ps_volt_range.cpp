#include "ps_volt_range.h"
#include "ps_analog_subsystem.h"

namespace ps
{
    const VoltRange VoltRange1V(String("1V"),-1.0, 1.0, VoltGain1X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange2V(String("2V"),-2.0, 2.0, VoltGain2X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange5V(String("5V"),-5.0, 5.0, VoltGain5X, AnalogSubsystem::MaxValueDac);
    const VoltRange VoltRange10V(String("10V"), -10.0, 10.0, VoltGain10X, AnalogSubsystem::MaxValueDac);

    VoltRangeFixedVector::VoltRangeFixedVector()
    {
        set(0,VoltRange1V);
        set(1,VoltRange2V);
        set(2,VoltRange5V);
        set(3,VoltRange10V);
    }

    VoltRangeFixedVector VoltRangeVector;

} // namespace ps
