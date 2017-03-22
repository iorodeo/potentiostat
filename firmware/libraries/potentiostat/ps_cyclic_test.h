#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H

#include <Arduino.h>
#include "ps_periodic_test.h"

namespace ps
{

    class CyclicTest : public PeriodicTest
    {
        public:

            CyclicTest();
            virtual float getValue(uint64_t t) const override;

    };

} // namespace ps

#endif
