#include "ps_system_state.h"

using namespace ps;

SystemState systemState;

void setup()
{
    Serial.begin(UsbSerialBaudrate);
    systemState.initialize();
    systemState.setTestTimerCallback(timerCallback);

    //systemState.startTestTimer();

}

void loop()
{
    systemState.processMessages();

    //systemState.serviceDataBuffer();
    //delay(50);
}

void timerCallback() 
{ 
    systemState.updateTestOnTimer(); 
}

void serialEvent()
{
    systemState.updateMessageData();
}
