#include "ps_curr_range.h"
#include "ps_analog_subsystem.h"

namespace ps
{
    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -10.0, 10.0, CurrGainPathIn3, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -10.0, 10.0, CurrGainPathIn4, AnalogSubsystemHW::MaxValueAin); 

    CurrRangeFixedVector::CurrRangeFixedVector()
    {
        set(0,CurrRange1uA);
        set(1,CurrRange10uA);
        set(2,CurrRange100uA);
        set(3,CurrRange1000uA);
    }

    CurrRangeFixedVector CurrRangeVector;

} // namespace ps
