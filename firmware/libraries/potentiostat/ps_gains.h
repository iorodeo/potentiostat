#ifndef PS_GAINS_H
#define PS_GAINS_H

#include <Arduino.h>

namespace ps
{

    enum VoltGain // Analog output voltage scaling factor 
    {
        VoltGain1X  = 0,   // [-1V,  +1V]   w/ default resisotors
        VoltGain2X  = 1,   // [-2V,  +2V]
        VoltGain5X  = 2,   // [-5V,  +5V]
        VoltGain10X = 3,   // [-10V  +10V]
        NumVoltGain = 4
    };

    enum CurrGainPath // TransImpedance Amplifiler Current gain path
    {
        CurrGainPathIn1 = 0,  // [-1uA,    +1uA]    w/ default resistors
        CurrGainPathIn2 = 1,  // [-10uA,   +10uA]   
        CurrGainPathIn3 = 2,  // [-100uA,  +100uA]  
        CurrGainPathIn4 = 3,  // [-1000uA, +1000uA] 
        CurrGainPathErr = 4,  // Incorrect path setting
        NumCurrGainPath = 5
    };

    const String VoltGainStringArray[NumVoltGain] = 
    {
        String("VoltGain1X"),
        String("VoltGain2X"),
        String("VoltGain5X"),
        String("VoltGain10X")
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
