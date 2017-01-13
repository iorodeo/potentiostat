#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"

using namespace ps;

CyclicTest cyclicTest;

IntervalTimer testTimer;

void testCallback()
{

}

void setup()
{
    AnalogSubsystem.initialize();
    AnalogSubsystem.setVoltRange(VoltRange2V);
    AnalogSubsystem.setCurrRange(CurrRange100uA);

    Serial.begin(115200);
}

void loop()
{


    delay(10);
}

