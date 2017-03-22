#ifndef PS_SINUSOID_TEST_H
#define PS_SINUSOID_TEST_H

#include "ps_periodic_test.h"
#include "ps_lookup_table.h"
#include <Arduino.h>

namespace ps
{

    class SinusoidTest : public PeriodicTest
    {
        public:

            static constexpr uint32_t LookupTableSize = 300;

            SinusoidTest();
            virtual void setAmplitude(float amplitude) override;
            virtual void setOffset(float offset) override;
            virtual float getValue(uint64_t t) const override;
            void updateLookupTable();

        protected:

            LookupTable<float,LookupTableSize> lookupTable_;


    };

} // namespace ps

#endif
