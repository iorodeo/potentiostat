#ifndef PS_SYSTEM_STATE_H
#define PS_SYSTEM_STATE_H
#include "ps_cyclic_test.h"
#include "ps_analog_subsystem.h"
#include "ps_voltammetry.h"

namespace ps
{

    class SystemState
    {
        public:

        protected:

            AnalogSubsystem analogSubsystem_;
            Voltammetry voltammetry_;

    };


} // namespace ps

#endif
