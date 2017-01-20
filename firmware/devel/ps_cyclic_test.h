#ifndef PS_CYCLIC_TEST_H
#define PS_CYCLIC_TEST_H
#include <Arduino.h>
#include "ps_periodic_test.h"

namespace ps
{

    class CyclicTest : public PeriodicTest
    {
        public:

            static const String NameString; 

            CyclicTest();
            virtual float getValue(uint64_t t) const;

    };

} // namespace ps




#endif
