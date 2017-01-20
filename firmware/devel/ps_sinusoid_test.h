#ifndef PS_SINUSOID_TEST_H
#define PS_SINUSOID_TEST_H
#include "ps_periodic_test.h"
#include "Array.h"
#include <Arduino.h>

namespace ps
{

    class SinusoidTest : public PeriodicTest
    {
        public:

            static constexpr uint32_t LookupTableSize = 200;

            static const String NameString;

            SinusoidTest();

            virtual float getValue(uint64_t t) const;

            void updateLookupTable();

        protected:

            Array<float,LookupTableSize> lookupTable_;


    };

} // namespace ps

#endif
