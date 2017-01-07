#ifndef PS_ANALOG_SUBSYSTEM_H
#define PS_ANALOG_SUBSYSTEM_H
#include "ps_pin_map.h"

namespace ps
{

    class AnalogSubsystem
    {
        public:

            enum VoltageRange 
            {
                VoltageRange1V, 
                VoltageRange2V,
                VoltageRange5V,
                VoltageRange10V
            };

            enum CurrentRange
            {
                CurrentRange1uA,
                CurrentRange10uA,
                CurrentRange100uA,
                CurrentRange1000uA
            };

            static const VoltageRange DefaultVoltageRange = VoltageRange1V;
            static const CurrentRange DefaultCurrentRange = CurrentRange10uA;

            AnalogSubsystem();
            void initialize();

            void setVoltageRange(VoltageRange value);
            void setCurrentRange(CurrentRange value);
    
        private:

    
    };

}

#endif
