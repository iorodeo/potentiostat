#ifndef PS_VOLTAMMETRY_H
#define PS_VOLTAMMETRY_H
#include "ps_constants.h"
#include "ps_base_test.h"
#include "ps_cyclic_test.h"
#include "ps_sinusoid_test.h"
#include "ps_constant_test.h"
#include "ps_linearsweep_test.h"
#include "ps_multistep_test.h"

namespace ps
{


    class Voltammetry
    {

        public:

            Voltammetry();
            BaseTest *getTestByName(String name);

            BaseTest baseTest;
            CyclicTest cyclicTest;
            SinusoidTest sinusoidTest;
            ConstantTest constantTest;
            LinearSweepTest linearSweepTest;
            MultiStepTest<2> chronoampTest;
            MultiStepTest<MultiStepMaxSize> multiStepTest;

    };

}

#endif
