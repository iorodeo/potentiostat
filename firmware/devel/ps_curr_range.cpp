#include "ps_curr_range.h"

namespace ps
{

    String currRangeToString(CurrRange value)
    {
        String currRangeString("");
        if (value < NumCurrRange)
        {
            currRangeString = CurrRangeStringArray[value];
        }
        return currRangeString;
    }


    CurrGainPath currRangeToGainPath(CurrRange value)
    {
        CurrGainPath currGainPath = CurrGainPathErr;
        if (value < NumCurrRange)
        {
            currGainPath = CurrRangeToGainPathMap[value];
        }
        return currGainPath;
    }


    CurrRange currGainPathToRange(CurrGainPath value)
    {
        CurrRange currRange = CurrRange(0);
        if (value < NumCurrGainPath)
        {
            currRange = CurrGainPathToRangeMap[value];
        }
        return currRange;
    }

    //float currRangeMaxValue(CurrRange currRange)
    //{

    //}

    //float currRangeMinValue(CurrRange currRange)
    //{
    //}

    //float AinToCurr(uint16_t valueDAC)
    //{
    //}

}
