#ifndef PS_LINEARSWEEP_TEST_H
#define PS_LINEARSWEEP_TEST_H
#include "ps_base_test.h"

namespace ps
{

    class LinearSweepTest : public BaseTest
    {

        public:

            LinearSweepTest();

            void setStartValue(float value);
            float getStartValue() const;

            void setFinalValue(float value);
            float getFinalValue() const;

            void setDuration(uint64_t duration);
            uint64_t getDuration() const;

            virtual bool isDone(uint64_t t) const; 
            virtual float getValue(uint64_t t) const; 
            virtual float getMaxValue() const; 
            virtual float getMinValue() const; 

        protected:

            float startValue_ = 0.0;
            float finalValue_ = 0.0;
            uint64_t duration_ = 0;

    };

} // namespace ps

#endif
