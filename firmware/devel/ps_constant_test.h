#ifndef PS_CONSTANT_TEST_H
#define PS_CONSTANT_TEST_H
#include "ps_base_test.h"

namespace ps
{

    class ConstantTest : public BaseTest
    {

        public:

            ConstantTest();


        protected:

            uint64_t duration_;
            float voltage_;


    };

} // namespace ps

#endif
