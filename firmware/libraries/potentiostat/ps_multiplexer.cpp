#include "ps_multiplexer.h"

#if defined MUX_CAPABLE
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
        initializeEnabledTable(true);
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
            return false;
        }
        else 
        {
            return true;
        }
    }


    bool Multiplexer::isConnectedRef()
    {
        if (digitalRead(MUX_REF_CONN))
        {
            return false;
        }
        else
        {
            return true;
        }
    }


    void Multiplexer::connectFirstEnabledWrkElect()
    {
        currWrkElect_ = NotConnected; 
        for (int i=0; i<NumMuxChan; i++) 
        {
            if (enabledTable_[i])
            {
                currWrkElect_ = indexToElectNum(i);
                connectWrkElect(currWrkElect_);
                break;
            }
        }
    }


    void Multiplexer::connectNextEnabledWrkElect()   
    {                                                
        int currIndex = electNumToIndex(currWrkElect_);
        for (int i=0; i<NumMuxChan; i++)
        {
            int nextIndex = (currIndex  + 1 + i) % NumMuxChan;
            if (enabledTable_[nextIndex])
            {
                connectWrkElect(indexToElectNum(nextIndex));
                break;
            }
        }
    }


    void Multiplexer::start()
    {
        running_ = true;
    }


    void Multiplexer::stop()
    {
        running_ = false;
    }


    void Multiplexer::enableWrkElect(int electNum)
    {
        if ((electNum > 0) && (electNum <= NumMuxChan))
        {
            int electIndex = electNumToIndex(electNum);
            enabledTable_[electIndex] = true;
        }
        numEnabled_ = countNumEnabled();
    }


    void Multiplexer::disableWrkElect(int electNum)
    {
        if ((electNum > 0) && (electNum <= NumMuxChan))
        {
            int electIndex = electNumToIndex(electNum);
            enabledTable_[electIndex] = false;
        }
        numEnabled_ = countNumEnabled();
    }


    void Multiplexer::enableAllWrkElect()
    {
        for (int i=0; i<NumMuxChan; i++) 
        {
            enabledTable_[i] = true;
        }
        numEnabled_ = NumMuxChan;
    }


    void Multiplexer::disableAllWrkElect()
    {
        for (int i=0; i<NumMuxChan; i++)
        {
            enabledTable_[i] = false;
        }
        numEnabled_ = 0;
    }


    void Multiplexer::setEnabledWrkElect(Array<int,NumMuxChan> enabledArray)
    {
        disableAllWrkElect();

        for (int i=0; i<int(enabledArray.size()); i++)
        {
            int electIndex = electNumToIndex(enabledArray[i]);
            if ((electIndex >= 0) && (electIndex < NumMuxChan))
            {
                enabledTable_[electIndex] = true;
            }
        }
        numEnabled_ = countNumEnabled();
    }


    Array<int,NumMuxChan> Multiplexer::getEnabledWrkElect()
    {
        Array<int,NumMuxChan> enabledArray;
        for (int i=0; i<NumMuxChan; i++)
        {
            if (enabledTable_[i])
            {
                int electNum = indexToElectNum(i);
                enabledArray.push_back(electNum);
            }
        }
        return enabledArray;
    } 
    
    
    bool Multiplexer::isWrkElectEnabled(int electNum)
    {
        int electIndex = electNumToIndex(electNum);
        if ((electIndex < 0) || (electIndex >= NumMuxChan))
        {
            return false;
        }
        else
        {
            return enabledTable_[electIndex];
        }
    }


    // Protected methods
    // ------------------------------------------------------------------------

    void Multiplexer::initializeEnabledTable(bool value)
    {
        for (int i=0; i<NumMuxChan; i++)
        {
            enabledTable_.push_back(value);
        }
        numEnabled_ = countNumEnabled();
    }

    void Multiplexer::setAllChanToGnd()
    {
        for (int i=0; i<NumMuxChan; i++)
        {
            digitalWrite(MuxToGndPin[i], LOW);
            digitalWrite(MuxToTiaPin[i], HIGH);
        }
    }


    int Multiplexer::countNumEnabled()
    {
        int count = 0;
        for (int i=0; i<NumMuxChan; i++)
        {
            if (enabledTable_[i])
            {
                count++;
            }
        }
        return count;
    }
    
}
#endif
