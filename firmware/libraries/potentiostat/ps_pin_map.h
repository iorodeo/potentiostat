#ifndef PS_PIN_MAP_H
#define PS_PIN_MAP_H

#include <Arduino.h>

namespace ps
{
    const int AD8250_GAIN_A0 = 0;
    const int AD8250_GAIN_A1 = 1;
    
    const int TIA_SW1_IN1 = 2;
    const int TIA_SW1_IN2 = 5;
    const int TIA_SW1_IN3 = 6;
    const int TIA_SW1_IN4 = 7;
    
    const int TIA_SW2_IN1 = 8;
    const int TIA_SW2_IN2 = 9;
    const int TIA_SW2_IN3 = 22;
    const int TIA_SW2_IN4 = 23;
    
    const int DAC_UNI_PIN = A14;
    const int TIA_OUT_UNI_PIN = A1;
    const int REF_ELECT_UNI_PIN = A2;
}

#endif
