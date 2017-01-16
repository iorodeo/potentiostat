#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"
#include "ps_system_state.h"
#include "ps_circular_buffer.h"

using namespace ps;

CircularBuffer<int,10> cb;

void setup()
{
    Serial.begin(115200);

    for (int i=0; i<5; i++)
    {
        cb.push_back(i);
    }

}


void loop()
{
    static bool state = true;

    Serial.print("size: ");
    Serial.println(int(cb.size()));
    Serial.print("pos_front: ");
    Serial.println(int(cb.pos_front()));
    Serial.print("pos_back: ");
    Serial.println(int(cb.pos_back()));
    Serial.print("front: ");
    Serial.println(cb.front());
    Serial.println();


    if (state)
    {
        cb.pop_back();
        state = false;
        Serial.println("pop_front");
    }
    else
    {
        cb.push_front(cb.front()+1);
        state = true;
        Serial.println("push_back");
    }
    Serial.println();
    delay(10);
}

//AnalogSubsystem analogSubsystem;
//CyclicTest cyclicTest;
//IntervalTimer testTimer;
//
//uint16_t timerPeriod = 200;
//uint16_t testPin = 31;
//
//
//void testTimerCallback()
//{
//    static bool state = false;
//    static double t = 0.0;
//    static double dt = double(timerPeriod)*1.0e-6;
//
//
//    float volt = cyclicTest.getValue(t);
//    analogSubsystem.setVolt(volt);
//
//    float curr = analogSubsystem.getCurr();
//
//    //if (cyclicTest.isDone(t))
//    //{
//    //    testTimer.end();
//    //}
//
//    t += dt;
//
//    if (state)
//    {
//        digitalWrite(testPin,LOW);
//        state = false;
//    }
//    else
//    {
//        digitalWrite(testPin,HIGH);
//        state = true;
//    }
//}
//
//void setup()
//{
//    analogSubsystem.initialize();
//    analogSubsystem.setVoltRange(VoltRange2V);
//    analogSubsystem.setCurrRange(CurrRange100uA);
//
//    cyclicTest.setPeriod(1.0);
//    cyclicTest.setAmplitude(2.0);
//    cyclicTest.setOffset(0.0);
//    cyclicTest.setLag(0.0);
//    cyclicTest.setNumCycles(10);
//
//    pinMode(testPin,OUTPUT);
//    digitalWrite(testPin,LOW);
//
//    testTimer.begin(testTimerCallback,timerPeriod);
//
//    Serial.begin(115200);
//}
//
//void loop()
//{
//
//
//    delay(1000);
//}

