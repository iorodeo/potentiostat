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

            static const unsigned int DefaultAnalogWriteResolution = 12;
            static const unsigned int DefaultAnalogReadResolution = 16;
            static const unsigned int DefaultAnalogReadAveraging = 16;
            static const unsigned int DefaultAnalogReference = INTERNAL;

            AnalogSubsystem();
            void initialize();

            void setVoltGain(VoltGain value);
            VoltGain getVoltGain();

            void setCurrGain(CurrGain value);
            CurrGain getCurrGain();

            void setVoltDAC(uint16_t value); // Set voltage output DAC value 16-bit
            uint16_t getVoltDAC();           // Get the DAC voltage output setting  

            uint16_t readCurrAin();          // Read analog input associated with the current-to-voltage 
                                             // converter (transimpedance amplifier).
                                             //
            uint16_t readRefElectAin();      // Read analog input associated with the refernce electrode

    };
}


#endif
