#define ARDUINOJSON_USE_LONG_LONG 1
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
    systemState.serviceDataBuffer();
}

void timerCallback() 
{ 
    systemState.updateTestOnTimer(); 
}

void serialEvent()
{
    systemState.updateMessageData();
}
