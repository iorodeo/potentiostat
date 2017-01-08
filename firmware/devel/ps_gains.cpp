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

    String currGainToString(CurrGain value)
    {
        String rval("");
        if (value < NumCurrGain)
        {
            rval = CurrGainStringArray[value];
        }
        return rval;
    }

}
