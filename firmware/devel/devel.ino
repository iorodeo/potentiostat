#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"
#include <array>

using namespace ps;

AnalogSubsystem analogSubsystem;
CyclicTest cyclicTest;
IntervalTimer testTimer;

uint16_t timerPeriod = 200;
uint16_t testPin = 31;


void testTimerCallback()
{
    static bool state = false;
    static double t = 0.0;
    static double dt = double(timerPeriod)*1.0e-6;

    std::array<int,3> x({1,2,3});


    float volt = cyclicTest.getValue(t);
    analogSubsystem.setVolt(volt);

    float curr = analogSubsystem.getCurr();

    if (cyclicTest.isDone(t))
    {
        testTimer.end();
    }

    t += dt;

    if (state)
    {
        digitalWrite(testPin,LOW);
        state = false;
    }
    else
    {
        digitalWrite(testPin,HIGH);
        state = true;
    }
}

void setup()
{
    analogSubsystem.initialize();
    analogSubsystem.setVoltRange(VoltRange2V);
    analogSubsystem.setCurrRange(CurrRange100uA);

    cyclicTest.setPeriod(1.0);
    cyclicTest.setAmplitude(1.0);
    cyclicTest.setOffset(0.5);
    cyclicTest.setLag(0.0);
    cyclicTest.setNumCycles(10);

    pinMode(testPin,OUTPUT);
    digitalWrite(testPin,LOW);

    testTimer.begin(testTimerCallback,timerPeriod);

    Serial.begin(115200);
}

void loop()
{

    delay(10);
}

