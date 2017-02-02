#include <cstdint>
#include "ps_constants.h"
#include "ps_analog_subsystem.h"
#include "ps_cyclic_test.h"
#include "ps_system_state.h"
#include "ps_circular_buffer.h"

using namespace ps;

SystemState systemState;
void timerCallback(); 

void setup()
{
    Serial.begin(115200);
    systemState.initialize();
    systemState.setTestTimerCallback(timerCallback);

    systemState.startTestTimer();
}

void loop()
{
    systemState.serviceDataBuffer();

    //systemState.debug();



    delay(50);
}


void timerCallback() 
{ 
    systemState.updateTestOnTimer(); 
}


