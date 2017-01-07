#include "ps_analog_subsystem.h"

ps::AnalogSubsystem analogSubsys;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    static int cnt = 0;
    Serial.print("cnt: ");
    Serial.println(cnt);
    cnt++;
    delay(100);
}
