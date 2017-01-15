#ifndef PS_CONSTANTS_H
#define PS_CONSTANTS_H
#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "Array.h"

namespace ps
{

    // Ranges for output voltage
    // --------------------------------------------------------------
    extern const VoltRange VoltRange1V; 
    extern const VoltRange VoltRange2V; 
    extern const VoltRange VoltRange5V; 
    extern const VoltRange VoltRange10V; 

    const int NumVoltRange = 4;
    extern Array<VoltRange,NumVoltRange> VoltRangeArray;


    // Ranges for input current
    // --------------------------------------------------------------
    extern const CurrRange CurrRange1uA; 
    extern const CurrRange CurrRange10uA; 
    extern const CurrRange CurrRange100uA; 
    extern const CurrRange CurrRange1000uA; 

    const int NumCurrRange = 4;
    extern Array<CurrRange,NumCurrRange> CurrRangeArray;

}

#endif
