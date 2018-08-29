#ifndef PS_MULTIPLEXER_H
#define PS_MULTIPLEXER_H

#include "ps_pin_map.h"
#include "ps_constants.h"
#include "third-party/Array/Array.h"

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

            // TODO
            // -------------------------------------------------------------------
            bool isRunning();
            void enableWrkElect(int electNum);
            void disableWrkElect(int electNum);
            void disableAllWrkElect();
            Array<int,NumMuxChan> getEnabledWrkElect();
            // -------------------------------------------------------------------

        protected:

            bool running_ = false;
            int currWrkElect_ = NotConnected;
            Array<int,NumMuxChan> enabledWrkElect_;

            void setAllChanToGnd();
            int electNumToIndex(int electNum);
    };

}

#endif
