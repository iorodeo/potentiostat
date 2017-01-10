#include "ps_gains.h"

namespace ps 
{
    String voltGainToString(VoltGain value)
    {
        String rval("");
        if (value < NumVoltGain)
        {
            rval = VoltGainStringArray[value];
        }
        return rval;
    }

    String currGainPathToString(CurrGainPath value)
    {
        String rval("");
        if (value < NumCurrGainPath)
        {
            rval = CurrGainPathStringArray[value];
        }
        return rval;
    }

}
