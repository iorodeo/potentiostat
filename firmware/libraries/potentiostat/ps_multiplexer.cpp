#include "ps_multiplexer.h"

namespace ps
{
    const int Multiplexer::MuxSwitchPin[NumMuxPin] = { 
        MUX_WRK1_TO_WRK,
        MUX_WRK1_TO_GND,
        MUX_WRK2_TO_WRK,
        MUX_WRK2_TO_GND,
        MUX_WRK3_TO_WRK,
        MUX_WRK3_TO_GND,
        MUX_WRK4_TO_WRK,
        MUX_WRK4_TO_GND,
        MUX_WRK5_TO_WRK,
        MUX_WRK5_TO_GND,
        MUX_WRK6_TO_WRK,
        MUX_WRK6_TO_GND,
        MUX_WRK7_TO_WRK,
        MUX_WRK7_TO_GND,
        MUX_CTR_CONN,
        MUX_REF_CONN,
    }; 

    const int Multiplexer::MuxToWrkPin[NumMuxChan] = {
        MUX_WRK1_TO_WRK,
        MUX_WRK2_TO_WRK,
        MUX_WRK3_TO_WRK,
        MUX_WRK4_TO_WRK,
        MUX_WRK5_TO_WRK,
        MUX_WRK6_TO_WRK,
        MUX_WRK7_TO_WRK,
    };

    const int Multiplexer::MuxToGndPin[NumMuxChan] = {
        MUX_WRK1_TO_GND,
        MUX_WRK2_TO_GND,
        MUX_WRK3_TO_GND,
        MUX_WRK4_TO_GND,
        MUX_WRK5_TO_GND,
        MUX_WRK6_TO_GND,
        MUX_WRK7_TO_GND,
    };

    Multiplexer::Multiplexer() 
    { }


    void Multiplexer::setupSwitchPins()
    {
        for (int i=0; i<NumMuxPin; i++) 
        {
            pinMode(MuxSwitchPin[i], OUTPUT);
        }
        setAllChanToGnd();
    }

    void Multiplexer::clearSwitchPins()
    {
        for (int i=0; i<NumMuxPin; i++) 
        {
            pinMode(MuxSwitchPin[i], INPUT);
            digitalWrite(MuxSwitchPin[i], LOW);
        }
    }

    void Multiplexer::setAllChanToGnd()
    {
        for (int i=0; i<NumMuxChan; i++)
        {
            digitalWrite(MuxToGndPin[i], HIGH);
        }
        for (int i=0; i<NumMuxChan; i++)
        {
            digitalWrite(MuxToWrkPin[i], LOW);
        }
    }
}
