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
            static const int MuxToTiaPin[NumMuxChan];
            static const int MuxToGndPin[NumMuxChan];
            static const int NotConnected = -1;

            Multiplexer();

            void setupSwitchPins();
            void clearSwitchPins();

            void connectCtrElect();
            void disconnectCtrElect();

            void connectRefElect();
            void disconnectRefElect();

            void connectWrkElect(int electNum);
            void disconnectWrkElect();

            int currentWrkElect();
            bool isConnectedWrk();
            bool isConnectedCtr();
            bool isConnectedRef();

        protected:

            int currWrkElect_ = NotConnected;

            void setAllChanToGnd();
            int electNumToIndex(int electNum);

    };

}

#endif
