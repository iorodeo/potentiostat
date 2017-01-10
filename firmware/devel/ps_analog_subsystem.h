#ifndef PS_ANALOG_SUBSYSTEM_H
#define PS_ANALOG_SUBSYSTEM_H
#include "ps_pin_map.h"
#include "ps_gains.h"
#include "ps_volt_range.h"
#include "ps_curr_range.h"

namespace ps
{

    class AnalogSubsystem
    {
        public:

            static const VoltGain DefaultVoltGain = VoltGain1X;
            static const CurrGainPath DefaultCurrGainPath = CurrGainPathIn1;

            static const uint16_t DefaultAnalogWriteResolution = 12;
            static const uint16_t DefaultAnalogReadResolution = 16;
            static const uint16_t DefaultAnalogReadAveraging = 16;
            static const uint8_t  DefaultAnalogReference = INTERNAL;

            static const uint16_t MaxValueDAC = (1 << DefaultAnalogWriteResolution)-1;
            static const uint16_t MidValueDAC = MaxValueDAC/2;

            //static const float MaxValueAin = 1.2;

            AnalogSubsystem();
            void initialize(); 

            void setVolt(float value); 
            float getVolt() const;     

            float getCurr() const;           
            float getRefElectVolt() const;   

            void setVoltRange(VoltRange value);  
            VoltRange getVoltRange() const;      

            void setCurrRange(CurrRange value);  
            CurrRange getCurrRange() const;      

            String getVoltRangeString() const;   
            String getCurrRangeString() const;   

            void setVoltGain(VoltGain value);    
            VoltGain getVoltGain() const;        

            void setCurrGainPath(CurrGainPath value); 
            CurrGainPath getCurrGainPath() const;

            String getVoltGainString() const;
            String getCurrGainPathString() const;

            void setValueDAC(uint16_t value); 
            uint16_t getValueDAC() const;     

            uint16_t getTransAmpAin() const;  
            uint16_t getRefElectAin() const;  

        protected:

            uint16_t valueDAC_;
            VoltRange voltRange_;
            CurrRange currRange_;

    };
}


#endif
