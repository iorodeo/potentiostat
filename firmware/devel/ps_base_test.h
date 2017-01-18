#ifndef PS_BASE_TEST_H
#define PS_BASE_TEST_H

namespace ps
{

    class BaseTest
    {

        public:

            BaseTest() {};
            virtual bool isDone(double t) const { return true; };
            virtual float getValue(double t) const { return 0.0; };
            virtual float getMaxValue() const { return 0.0; };
            virtual float getMinValue() const { return 0.0; };
    };

}

#endif
