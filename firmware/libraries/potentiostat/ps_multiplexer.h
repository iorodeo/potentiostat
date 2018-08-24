#ifndef PS_MULTIPLEXER_H
#define PS_MULTIPLEXER_H

#include "ps_pin_map.h"
#include "ps_constants.h"

namespace ps
{

    class Multiplexer
    {
        public:

            static const int MuxSwitchPin[NumMuxPin]; 
            static const int MuxToWrkPin[NumMuxChan];
            static const int MuxToGndPin[NumMuxChan];

            Multiplexer();

            void setupSwitchPins();
            void clearSwitchPins();
            void setAllChanToGnd();

        protected:

    };

}

#endif
