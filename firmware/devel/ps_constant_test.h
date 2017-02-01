#ifndef PS_CONSTANT_TEST_H
#define PS_CONSTANT_TEST_H
#include "ps_base_test.h"

namespace ps
{

    class ConstantTest : public BaseTest
    {

        public:

            ConstantTest();

            void setDuration(uint64_t duration);
            uint64_t getDuration();

            virtual bool isDone(uint64_t t) const override;
            virtual float getValue(uint64_t t) const override; 
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 

        protected:

            uint64_t duration_;
            float voltage_;


    };

} // namespace ps

#endif
