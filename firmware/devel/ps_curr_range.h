#ifndef PS_CURR_RANGE_H
#define PS_CURR_RANGE_H
#include <Arduino.h>
#include "ps_gains.h"

namespace ps
{
    // TO DO .. modifiy so that CurrRange is class

#ifdef PS_CURR_RANGE_CUSTOM

#else

    enum CurrRange
    {
        CurrRange1uA     = 0,
        CurrRange10uA    = 1,
        CurrRange100uA   = 2,
        CurrRange1000uA  = 3,
        CurrRangeErr     = 4,
        NumCurrRange     = 5
    };


    const String CurrRangeStringArray[NumCurrRange] = 
    {
        String("1uA"),
        String("10uA"),
        String("100uA"),
        String("1000uA"),
        String("error")
    };


    const CurrGainPath CurrRangeToGainPathMap[NumCurrRange] =
    {
        CurrGainPathIn1,   // CurrRange1uA
        CurrGainPathIn2,   // CurrRange10uA
        CurrGainPathIn3,   // CurrRange100uA
        CurrGainPathIn4,   // CurrRange1000uA
        CurrGainPathErr,
    };


    const CurrRange CurrGainPathToRangeMap[NumCurrGainPath] =
    {
        CurrRange1uA,     // CurrGainPathIn1
        CurrRange10uA,    // CurrGainPathIn2
        CurrRange100uA,   // CurrGainPathIn3
        CurrRange1000uA,  // CurrGainPathIn4
        CurrRangeErr
    };

    const float CurrRangeMaxValueArray[NumCurrRange] = { 1.0, 10.0, 100.0, 1000.0 };
    const float CurrRangeMinValueArray[NumCurrRange] = {-1.0, -10.0, -100.0, -1000};

#endif

    String currRangeToString(CurrRange value);
    CurrGainPath currRangeToGainPath(CurrRange value);
    CurrRange currGainPathToRange(CurrGainPath value);
    //float currRangeMaxValue(CurrRange currRange);
    //float currRangeMinValue(CurrRange currRange);
    //float AinToCurr(uint16_t valueDAC);
    
}

#endif
