#include "ps_analog_subsystem.h"

using namespace ps;

void setup()
{
    AnalogSubsystem.initialize();
    AnalogSubsystem.setVoltRange(VoltRange5V);
    AnalogSubsystem.setCurrRange(CurrRange100uA);

    VoltRange range = VoltRangeVector[0];


    Serial.begin(115200);
}

void loop()
{

    //for (auto range : VoltRangeVector)
    //{
    //    Serial.println(range.name());
    //}
    delay(100);

}
