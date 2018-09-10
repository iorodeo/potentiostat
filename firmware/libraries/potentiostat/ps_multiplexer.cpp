#include "ps_multiplexer.h"

namespace ps
{
    const int Multiplexer::MuxSwitchPin[NumMuxPin] = { 
        MUX_WRK1_TO_TIA,
        MUX_WRK1_TO_GND,
        MUX_WRK2_TO_TIA,
        MUX_WRK2_TO_GND,
        MUX_WRK3_TO_TIA,
        MUX_WRK3_TO_GND,
        MUX_WRK4_TO_TIA,
        MUX_WRK4_TO_GND,
        MUX_WRK5_TO_TIA,
        MUX_WRK5_TO_GND,
        MUX_WRK6_TO_TIA,
        MUX_WRK6_TO_GND,
        MUX_WRK7_TO_TIA,
        MUX_WRK7_TO_GND,
        MUX_CTR_CONN,
        MUX_REF_CONN,
    }; 

    const int Multiplexer::MuxToTiaPin[NumMuxChan] = {
        MUX_WRK1_TO_TIA,
        MUX_WRK2_TO_TIA,
        MUX_WRK3_TO_TIA,
        MUX_WRK4_TO_TIA,
        MUX_WRK5_TO_TIA,
        MUX_WRK6_TO_TIA,
        MUX_WRK7_TO_TIA,
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

    // Public methods
    // -------------------------------------------------------------------

    Multiplexer::Multiplexer() 
    { 
        enableAllWrkElect();
    }


    void Multiplexer::setupSwitchPins()
    {
        for (int i=0; i<NumMuxPin; i++) 
        {
            pinMode(MuxSwitchPin[i], OUTPUT);
        }
        disconnectCtrElect();
        disconnectRefElect();
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


    void Multiplexer::connectCtrElect()
    {
        digitalWrite(MUX_CTR_CONN, LOW);
    }


    void Multiplexer::disconnectCtrElect()
    {
        digitalWrite(MUX_CTR_CONN, HIGH);
    }


    void Multiplexer::connectRefElect()
    {
        digitalWrite(MUX_REF_CONN, LOW);
    }


    void Multiplexer::disconnectRefElect()
    {
        digitalWrite(MUX_REF_CONN, HIGH);
    }


    void Multiplexer::connectWrkElect(int electNum)
    {
        // Connects working electrode (electNum) to the transimpedance 
        // amplifier using 'make-before-break' method 
        
        int index = electNumToIndex(electNum);

        if ((index >= 0) && (index < NumMuxChan))
        {
            // Disconnect current mux chan (if any) from TIA 
            disconnectWrkElect();

            // Make connection between electNum mux chan and TIA 
            digitalWrite(MuxToTiaPin[index], LOW);

            // Break connection between electNum mux chan and ground
            digitalWrite(MuxToGndPin[index], HIGH);

            currWrkElect_ = electNum;
        }
    }

    void Multiplexer::disconnectWrkElect()
    {
        // Disconnected working electrode from transimpedance amplifier
        // using 'make-before-break' method.
        
        int index = electNumToIndex(currWrkElect_);

        if ( (currWrkElect_ != NotConnected)  && (index >=0) && (index < NumMuxChan))
        {
            // Make connection between electNum mux chan and ground
            digitalWrite(MuxToGndPin[index], LOW);

            // Break connection between electNum mux chan and TIA
            digitalWrite(MuxToTiaPin[index], HIGH);

            currWrkElect_ = NotConnected;
        }
    }


    int Multiplexer::currentWrkElect()
    {
        return currWrkElect_;
    }


    bool Multiplexer::isConnectedWrk()
    {
        if (currWrkElect_ == NotConnected)
        {
            return false;
        }
        else 
        {
            return true;
        }
    }


    bool Multiplexer::isConnectedCtr()
    {
        if (digitalRead(MUX_CTR_CONN)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }


    bool Multiplexer::isConnectedRef()
    {
        if (digitalRead(MUX_REF_CONN))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    // TODO
    // -------------------------------------------------------------------------

    void Multiplexer::connectFirstEnabledWrkElect()
    {
        if (numEnabledWrkElect() > 0)
        {
            currWrkElect_ = enabledWrkElectArray_[0];
        }
    }


    void Multiplexer::connectNextEnabledWrkElect()   
    {                                                
    }


    void Multiplexer::start()
    {
        running_ = true;
    }


    void Multiplexer::stop()
    {
        running_ = false;
    }


    bool Multiplexer::isRunning()
    {
        return running_;
    }


    void Multiplexer::enableWrkElect(int electNum)
    {
        if ((electNum <= 0) || (electNum > NumMuxChan))
        {
            return;
        }

        Array<int,NumMuxChan> newEnabledArray;
        bool electAdded = false;

        for (size_t i=0; i<enabledWrkElectArray_.size(); i++)
        {
            if ((electNum < enabledWrkElectArray_[i]) && !electAdded)
            {
                newEnabledArray.push_back(electNum);
                electAdded = true;
            }
            newEnabledArray.push_back(enabledWrkElectArray_[i]);
        }
        if (!electAdded)
        {
            newEnabledArray.push_back(electNum);
        }
        enabledWrkElectArray_ = newEnabledArray;
    }


    void Multiplexer::disableWrkElect(int electNum)
    {
        if ((electNum <= 0) || (electNum > NumMuxChan))
        {
            return;
        }

        Array<int,NumMuxChan> newEnabledArray;
        for (size_t i=0; i<enabledWrkElectArray_.size(); i++)
        {
            if (enabledWrkElectArray_[i] != electNum)
            {
                newEnabledArray.push_back(enabledWrkElectArray_[i]);
            }
        }
    }

    void Multiplexer::enableAllWrkElect()
    {
        for (int i=0; i<NumMuxChan; i++) 
        {
            int electNum = indexToElectNum(i);
            enabledWrkElectArray_.push_back(electNum);
        }
    }


    void Multiplexer::disableAllWrkElect()
    {
        enabledWrkElectArray_.clear();
    }


    void Multiplexer::setEnabledWrkElect(Array<int,NumMuxChan> enabledArray)
    {
        enabledWrkElectArray_ = enabledArray;
    }


    Array<int,NumMuxChan> Multiplexer::getEnabledWrkElect()
    {
        return enabledWrkElectArray_;
    }

    int Multiplexer::numEnabledWrkElect()
    {
        return enabledWrkElectArray_.size();
    }


    // ------------------------------------------------------------------------



    // Protected methods
    // ------------------------------------------------------------------------
    
    void Multiplexer::setAllChanToGnd()
    {
        for (int i=0; i<NumMuxChan; i++)
        {
            digitalWrite(MuxToGndPin[i], LOW);
            digitalWrite(MuxToTiaPin[i], HIGH);
        }
    }

    int Multiplexer::electNumToIndex(int electNum)
    {
        return electNum - 1;
    }

    int Multiplexer::indexToElectNum(int index)
    {
        return index + 1;
    }
    
}
