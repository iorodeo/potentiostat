#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"


ps::AnalogSubsystem analogSubsys;

void setup()
{
    analogSubsys.initialize();
    analogSubsys.setVoltRange(ps::VoltRange5V);
    analogSubsys.setCurrRange(ps::CurrRange100uA);

    Serial.begin(115200);
}

void loop()
{
    static int cnt = 0;
    static int maxCnt = 1000;
    static float minValue = -3.0;
    static float maxValue =  3.0;

    float value = minValue + float(cnt)/float(maxCnt)*(maxValue - minValue);
    analogSubsys.setVolt(value);

    Serial.print("cnt:   ");
    Serial.println(cnt);
    Serial.print("value: ");
    Serial.println(value);
    Serial.println();

    cnt++;
    if (cnt >= maxCnt)
    {
        cnt = 0;
    }
    delay(10);


    //static int cnt = 0;
    //ps::CyclicTest cyclicTest = ps::CyclicTest::getInstance();

    //uint64_t time = 10000*cnt;
    //uint16_t value = cyclicTest.getValue(time);

    //Serial.print("time:        ");
    //Serial.println(long(time));
    //Serial.print("value:       ");
    //Serial.println(value);
    //Serial.print("periodCount: ");
    //Serial.println(cyclicTest.getPeriodCount(time));
    //Serial.println();

    //cnt++;
    //delay(10);
}
