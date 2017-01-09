#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"


ps::AnalogSubsystem analogSubsys;

void setup()
{
    //analogSubsys.initialize();
    //analogSubsys.setVoltGain(ps::VoltGain2X);
    //analogSubsys.setCurrGain(ps::CurrGainPathIn3);

    Serial.begin(115200);
}

void loop()
{
    static int cnt = 0;

    ps::CyclicTest cyclicTest = ps::CyclicTest::getInstance();

    uint64_t time = 10000*cnt;
    uint16_t value = cyclicTest.getValue(time);

    Serial.print("time:        ");
    Serial.println(long(time));
    Serial.print("value:       ");
    Serial.println(value);
    Serial.print("periodCount: ");
    Serial.println(cyclicTest.getPeriodCount(time));
    Serial.println();

    cnt++;
    delay(10);
}
