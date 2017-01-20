#ifndef PS_VOLTAMMETRY_H
#define PS_VOLTAMMETRY_H
#include "ps_base_test.h"
#include "ps_cyclic_test.h"
#include "ps_sinusoid_test.h"

namespace ps
{

    class Voltammetry
    {
        public:

            BaseTest baseTest;
            CyclicTest cyclicTest;
            SinusoidTest sinusoidTest;
    };

}

#endif
