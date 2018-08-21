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

    // Multiplexer switch pins
    const int MUX_WRK1_TO_WRK = 24;
    const int MUX_WRK1_TO_GND = 28;
    const int MUX_WRK2_TO_WRK = 25;
    const int MUX_WRK2_TO_GND = 29;
    const int MUX_WRK3_TO_WRK = 26;
    const int MUX_WRK3_TO_GND = 30;
    const int MUX_WRK4_TO_WRK = 27;
    const int MUX_WRK4_TO_GND = 31;
    const int MUX_WRK5_TO_WRK = 4;
    const int MUX_WRK5_TO_GND = 11;
    const int MUX_WRK6_TO_WRK = 19;
    const int MUX_WRK6_TO_GND = 13;
    const int MUX_WRK7_TO_WRK = 18;
    const int MUX_WRK7_TO_GND = 10;
    const int MUX_CTR_CONN = 3;
    const int MUX_REF_CONN = 12;

}

#endif
