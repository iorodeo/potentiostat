#ifndef PS_GAINS_H
#define PS_GAINS_H

#include <Arduino.h>
#include "ps_hardware_defs.h"

namespace ps
{

#if defined(VOLTAGE_VARIANT_AD8250) || defined(VOLTAGE_VARIANT_10V)

    enum VoltGain // Analog output voltage scaling factor 
    {
        VoltGain1X  = 0,   // [-1V,  +1V]   
        VoltGain2X  = 1,   // [-2V,  +2V]
        VoltGain5X  = 2,   // [-5V,  +5V]
        VoltGain10X = 3,   // [-10V, +10V]
        NumVoltGain = 4
    };

    const String VoltGainStringArray[NumVoltGain] = 
    {
        String("VoltGain1X"),
        String("VoltGain2X"),
        String("VoltGain5X"),
        String("VoltGain10X")
    };

#elif defined VOLTAGE_VARIANT_AD8251

    enum VoltGain // Analog output voltage scaling factor 
    {
        VoltGain1X  = 0,   // [-1V,  +1V]   
        VoltGain2X  = 1,   // [-2V,  +2V]
        VoltGain4X  = 2,   // [-4V,  +4V]
        VoltGain8X  = 3,   // [-8V,  +8V]
        VoltGain10X = 4,   // [-10V, +10V] // used for reference input
        NumVoltGain = 5
    };

    const String VoltGainStringArray[NumVoltGain] = 
    {
        String("VoltGain1X"),
        String("VoltGain2X"),
        String("VoltGain4X"),
        String("VoltGain8X"),
        String("VoltGain10X")
    };

#else
#   error "VOLTAGE_VARIANT must be specified"
#endif

    enum CurrGainPath // TransImpedance Amplifiler Current gain path
    {
        CurrGainPathIn1 = 0,  // [-1uA,    +1uA]    w/ default resistors
        CurrGainPathIn2 = 1,  // [-10uA,   +10uA]   
        CurrGainPathIn3 = 2,  // [-100uA,  +100uA]  
        CurrGainPathIn4 = 3,  // [-1000uA, +1000uA] 
        CurrGainPathErr = 4,  // Incorrect path setting
        NumCurrGainPath = 5
    };


    const String CurrGainPathStringArray[NumCurrGainPath] = 
    {
        String("CurrGainPathIn1"),
        String("CurrGainPathIn2"),
        String("CurrGainPathIn3"),
        String("CurrGainPathIn4"),
        String("CurrGainPathErr")
    };

    String voltGainToString(VoltGain value);

    String currGainPathToString(CurrGainPath value);

}
#endif
