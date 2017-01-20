#ifndef PS_BASE_TEST_H
#define PS_BASE_TEST_H
#include <Arduino.h>

namespace ps
{

    class BaseTest
    {

        public:

            static const String NameString;

            BaseTest() {};
            virtual bool isDone(uint64_t t) const { return true; };
            virtual float getValue(uint64_t t) const { return 0.0; };
            virtual float getMaxValue() const { return 0.0; };
            virtual float getMinValue() const { return 0.0; };
    };


}

#endif
