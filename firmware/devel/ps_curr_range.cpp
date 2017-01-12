#include "ps_curr_range.h"
#include "ps_analog_subsystem.h"

namespace ps
{

    CurrRange::CurrRange(String name, float minCurr, float maxCurr, CurrGainPath gainPath, uint16_t maxAin)
        : name_(name), minCurr_(minCurr), maxCurr_(maxCurr), gainPath_(gainPath), maxAin_(maxAin)
    { }

    String CurrRange::name() const
    {
        return name_;
    }


    float CurrRange::minCurr() const
    {
        return minCurr_;
    }


    float CurrRange::maxCurr() const
    {
        return maxCurr_;
    }


    uint16_t CurrRange::maxAin() const
    {
        return maxAin_;
    }


    CurrGainPath CurrRange::gainPath() const
    {
        return gainPath_;
    }


    String CurrRange::gainPathString() const
    {
        return currGainPathToString(gainPath_);
    }


    float CurrRange::ainToCurr(uint16_t ain)
    {
        float curr = 0.0;
        return curr;
    }


    uint16_t CurrRange::CurrToAin(float curr)
    {
        uint16_t ain = 0;
        return ain;
    }


    const CurrRange CurrRange1uA("1uA", -1.0, 1.0, CurrGainPathIn1, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange10uA("10uA", -10.0, 10.0, CurrGainPathIn2, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange100uA("100uA", -10.0, 10.0, CurrGainPathIn3, AnalogSubsystemHW::MaxValueAin); 
    const CurrRange CurrRange1000uA("1000uA", -10.0, 10.0, CurrGainPathIn4, AnalogSubsystemHW::MaxValueAin); 

    // CurrRangeVector methods
    // ----------------------------------------------------------------------------------------------

    CurrRangeFixedVector::CurrRangeFixedVector()
    {
        set(0,CurrRange1uA);
        set(1,CurrRange10uA);
        set(2,CurrRange100uA);
        set(3,CurrRange1000uA);
    }

    CurrRangeFixedVector CurrRangeVector;

} // namespace ps
