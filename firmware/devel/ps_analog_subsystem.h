#ifndef PS_ANALOG_SUBSYSTEM_H
#define PS_ANALOG_SUBSYSTEM_H
#include "ps_pin_map.h"
#include "ps_gains.h"

namespace ps
{

    class AnalogSubsystem
    {
        public:

            static const VoltGain DefaultVoltGain = VoltGain1X;
            static const CurrGain DefaultCurrGain = CurrGainPathIn1;

            static const uint16_t DefaultAnalogWriteResolution = 12;
            static const uint16_t DefaultAnalogReadResolution = 16;
            static const uint16_t DefaultAnalogReadAveraging = 16;
            static const uint8_t  DefaultAnalogReference = INTERNAL;

            AnalogSubsystem();
            void initialize();

            void setVoltGain(VoltGain value);
            void setCurrGain(CurrGain value);

            VoltGain getVoltGain() const;
            CurrGain getCurrGain() const;

            String getVoltGainString() const;
            String getCurrGainString() const;

            void setVoltDAC(uint16_t value); // Set voltage output DAC value 16-bit
            uint16_t getVoltDAC() const;     // Get the DAC voltage output setting  

            uint16_t readCurrAin();          // Read analog input associated with the transimpedance amplifier 
                                             
            uint16_t readRefElectAin();      // Read analog input associated with the refernce electrode

            uint16_t getMaxValueDAC() const;
            uint16_t getZeroValueDAC() const;

    };
}


#endif
