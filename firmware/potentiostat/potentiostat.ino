#include "potentiostat.h"

using namespace ps;

SystemState systemState;

void setup()
{
    Serial.begin(UsbSerialBaudrate);
    systemState.initialize();
    systemState.setTestTimerCallback(timerCallback);
}

void loop()
{
    systemState.updateMessageData();
    systemState.processMessages();
    systemState.serviceDataBuffer();
}

void timerCallback() 
{ 
    systemState.updateTestOnTimer(); 
}

