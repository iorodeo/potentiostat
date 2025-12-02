#ifndef PS_PIN_MAP_H
#define PS_PIN_MAP_H
#include <Arduino.h>
#include "ps_hardware_defs.h"

namespace ps
{
#if defined HARDWARE_VERSION_0P1 
    constexpr int AD8250_GAIN_A0 = 0;
    constexpr int AD8250_GAIN_A1 = 1;
    constexpr int TIA_SW1_IN1 = 2;
    constexpr int TIA_SW1_IN2 = 5;
    constexpr int TIA_SW1_IN3 = 6;
    constexpr int TIA_SW1_IN4 = 7;
    constexpr int TIA_SW2_IN1 = 8;
    constexpr int TIA_SW2_IN2 = 9;
    constexpr int TIA_SW2_IN3 = 22;
    constexpr int TIA_SW2_IN4 = 23;
#elif defined (HARDWARE_VERSION_0P2) && defined (DEVBOARD_TEENSY)
    constexpr int DAC_GAIN_A0 = 0;
    constexpr int DAC_GAIN_A1 = 1;
    constexpr int TIA_GAIN_A0 = 5;
    constexpr int TIA_GAIN_A1 = 6; 
    constexpr int REF_GAIN_A0 = 20;
    constexpr int REF_GAIN_A1 = 21;
    constexpr int SW_CTR_ELECT = 7;
    constexpr int SW_REF_ELECT = 8;
    constexpr int SW_WRK_ELECT = 9;
#elif defined (HARDWARE_VERSION_0P2) && defined (DEVBOARD_ITSY_BITSY)
    constexpr int DAC_GAIN_A0 = 3;
    constexpr int DAC_GAIN_A1 = 4;
    constexpr int TIA_GAIN_A0 = 9;
    constexpr int TIA_GAIN_A1 = 10; 
    constexpr int REF_GAIN_A0 = 18;
    constexpr int REF_GAIN_A1 = 19;
    constexpr int SW_CTR_ELECT = 11;
    constexpr int SW_REF_ELECT = 12;
    constexpr int SW_WRK_ELECT = 13;
    constexpr int ExpDioPin3 = 7;
    constexpr int ExpDioPin4 = 17;
    constexpr int ExpDioPin5 = 22;
    constexpr int ExpDioPin6 = 21;
    constexpr int ExpDioPin7 = 23;
    constexpr int ExpDioPin8 = 25;
    constexpr int ExpDioPin9 = 24;
    constexpr int ExpDioPin10 = 2;
#else
    #error "HARDWARE_VERSION must be specified"
#endif 

#if defined DEVBOARD_TEENSY 
    constexpr int DAC_UNI_PIN = A14;
    constexpr int TIA_OUT_UNI_PIN = A1;
    constexpr int REF_ELECT_UNI_PIN = A2;
#elif defined DEVBOARD_ITSY_BITSY 
    constexpr int DAC_UNI_PIN = A0;
    constexpr int TIA_OUT_UNI_PIN = A1;
    constexpr int REF_ELECT_UNI_PIN = A2;
#else
    #error "DEVBOARD must be specified"
#endif

#if defined MUX_CAPABLE  
    #if defined DEVBOARD_TEENSY
    // Multiplexer switch pins
    constexpr int MUX_WRK1_TO_TIA = 24;
    constexpr int MUX_WRK1_TO_GND = 28;
    constexpr int MUX_WRK2_TO_TIA = 25;
    constexpr int MUX_WRK2_TO_GND = 29;
    constexpr int MUX_WRK3_TO_TIA = 26;
    constexpr int MUX_WRK3_TO_GND = 30;
    constexpr int MUX_WRK4_TO_TIA = 27;
    constexpr int MUX_WRK4_TO_GND = 31;
    constexpr int MUX_WRK5_TO_TIA = 4;
    constexpr int MUX_WRK5_TO_GND = 11;
    constexpr int MUX_WRK6_TO_TIA = 19;
    constexpr int MUX_WRK6_TO_GND = 13;
    constexpr int MUX_WRK7_TO_TIA = 18;
    constexpr int MUX_WRK7_TO_GND = 10;
    constexpr int MUX_CTR_CONN = 3;
    constexpr int MUX_REF_CONN = 12;
    #else
        #error "DEVBOARD doesn't support multiplexer"
    #endif
#endif

}

#endif
