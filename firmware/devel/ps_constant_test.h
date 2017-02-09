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
            uint64_t getDuration() const;

            void setValue(float value);
            virtual float getValue(uint64_t t) const override; 

            virtual bool isDone(uint64_t t) const override;
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 
            virtual void getParam(JsonObject &json);
            virtual void setParam(JsonObject &json);

        protected:

            uint64_t duration_ = 5000000;
            float value_ = 1.0;
    };

} // namespace ps

#endif
