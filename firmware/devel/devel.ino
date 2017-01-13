#include "ps_analog_subsystem.h"

using namespace ps;

void setup()
{
    AnalogSubsystem.initialize();
    AnalogSubsystem.setVoltRange(VoltRange5V);
    AnalogSubsystem.setCurrRange(CurrRange100uA);

    Serial.begin(115200);
}

void loop()
{

    delay();
}
