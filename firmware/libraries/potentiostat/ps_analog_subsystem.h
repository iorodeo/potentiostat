#ifndef PS_ANALOG_SUBSYSTEM_H
#define PS_ANALOG_SUBSYSTEM_H

#include "ps_hardware_variant_defs.h"
#include "ps_pin_map.h"
#include "ps_gains.h"
#include "ps_volt_range.h"
#include "ps_curr_range.h"
#include "ps_return_status.h"

namespace ps
{

    class AnalogSubsystem
    {
        public:

            static const uint16_t DefaultAnalogWriteResolution = 12;
            static const uint16_t DefaultAnalogReadResolution = 16;
            static const uint16_t DefaultAnalogReadAveraging = 16;
            static const uint8_t  DefaultAnalogReference = INTERNAL;

            static const uint16_t MaxValueAin = uint16_t((uint32_t(1) << DefaultAnalogReadResolution) -1);
            static const uint16_t MaxValueDac = uint16_t((uint32_t(1) << DefaultAnalogWriteResolution)-1);
            static const uint16_t MidValueDac = MaxValueDac/2;

            AnalogSubsystem();
            void initialize(); 

            void setVolt(float value); 
            float getVolt() const;     
            
            float getCurr() const;           
            float getRefElectVolt() const;   

            void setVoltRange(VoltRange range);  
            VoltRange getVoltRange() const;      
            bool autoVoltRange(float minVolt, float maxVolt);

            void setCurrRange(CurrRange range);  
            CurrRange getCurrRange() const;      

            ReturnStatus setVoltRangeByName(String voltRangeName);
            String getVoltRangeName() const;   

            ReturnStatus setCurrRangeByName(String currRangeName);
            String getCurrRangeName() const;   

#if defined HARDWARE_VERSION_0P2
            void setRefElectVoltRange(VoltRange range);
            VoltRange getRefElectVoltRange() const;

            ReturnStatus setRefElectVoltRangeByName(String voltRangeName);
            String getRefElectVoltRangeName() const;
#endif


        protected:

            uint16_t valueDac_;
            VoltRange voltRange_;
            CurrRange currRange_;

            void setVoltGain(VoltGain value);    
            VoltGain getVoltGain() const;        

            void setCurrGainPath(CurrGainPath value); 
            CurrGainPath getCurrGainPath() const;

            String getVoltGainString() const;
            String getCurrGainPathString() const;

            void setValueDac(uint16_t value); 
            uint16_t getValueDac() const;     

            uint16_t getTransAmpAin() const;  
            uint16_t getRefElectAin() const;  

#if defined HARDWARE_VERSION_0P2
            VoltRange refElectVoltRange_;
            void setRefElectVoltGain(VoltGain value);
            VoltGain getRefElectVoltGain() const;
#endif

    };

} // namespace ps


#endif
