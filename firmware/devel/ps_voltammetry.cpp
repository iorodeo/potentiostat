#include "ps_voltammetry.h"

namespace ps
{

    Voltammetry::Voltammetry()
    {
        chronoampTest.setNumStep(2);
        chronoampTest.setName("chronoamp");
    }

    BaseTest *Voltammetry::getTestByName(String name)
    {
        return &baseTest;
    }

}
