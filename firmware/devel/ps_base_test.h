#ifndef PS_BASE_TEST_H
#define PS_BASE_TEST_H
#include <Arduino.h>

namespace ps
{

    class BaseTest
    {

        public:

            static const String NameString;

            BaseTest();

            virtual bool isDone(uint64_t t) const; 
            virtual void reset();

            virtual float getValue(uint64_t t) const; 
            virtual float getMaxValue() const; 
            virtual float getMinValue() const; 

            virtual void setQuietTime(uint64_t quietTime);
            virtual uint64_t getQuietTime() const;

            virtual void setQuietValue(float value);
            virtual uint64_t getQuietValue() const;

        protected:

            uint64_t quietTime_ = 0;
            float quietValue_ = 0.0;

    };

}

#endif
