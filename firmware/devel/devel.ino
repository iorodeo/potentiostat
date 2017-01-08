#include "ps_analog_subsystem.h"


ps::AnalogSubsystem analogSubsys;

void setup()
{
    analogSubsys.initialize();
    analogSubsys.setVoltGain(ps::VoltGain2X);
    analogSubsys.setCurrGain(ps::CurrGainPathIn2);

    Serial.begin(115200);
}

void loop()
{
    static int cnt = 0;

    Serial.print("cnt: ");
    Serial.println(cnt);

    String voltGainString = analogSubsys.getVoltGainString();
    String currGainString = analogSubsys.getCurrGainString();

    Serial.print("voltGain: ");
    Serial.println(voltGainString);
    Serial.print("currGain: ");
    Serial.println(currGainString);
    Serial.println();

    cnt++;

    delay(100);
}
