#ifndef PS_MULTIPLEXER_H
#define PS_MULTIPLEXER_H

#include "ps_pin_map.h"
#include "ps_constants.h"
#include "ps_return_status.h"
#include "Array.h"

#if defined MUX_CAPABLE
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

            void connectFirstEnabledWrkElect();
            void connectNextEnabledWrkElect();   

            void start();  
            void stop();
            bool isRunning();

            void enableWrkElect(int electNum);
            void disableWrkElect(int electNum);

            void enableAllWrkElect();
            void disableAllWrkElect();

            void setEnabledWrkElect(Array<int,NumMuxChan> enabledArray);
            Array<int,NumMuxChan> getEnabledWrkElect();
            bool isWrkElectEnabled(int electNum);

            int numEnabledWrkElect();
            int electNumToIndex(int electNum);
            int indexToElectNum(int index);

        protected:

            bool running_ = false;
            volatile int currWrkElect_ = NotConnected;

            int numEnabled_ = 0;
            Array<bool,NumMuxChan> enabledTable_;

            void setAllChanToGnd();
            void initializeEnabledTable(bool value);

            int countNumEnabled();

    };

    inline int Multiplexer::currentWrkElect()
    {
        return currWrkElect_;
    }

    inline bool Multiplexer::isRunning()
    {
        return running_;
    }

    inline int Multiplexer::numEnabledWrkElect()
    {
        return numEnabled_;
    }

    inline int Multiplexer::electNumToIndex(int electNum)
    {
        return electNum - 1;
    }

    inline int Multiplexer::indexToElectNum(int index)
    {
        return index + 1;
    }

}

#endif

#endif
