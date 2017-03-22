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

            virtual bool isDone(uint64_t t) const override; 
            virtual uint64_t getDoneTime() const override;
            virtual float getValue(uint64_t t) const override; 
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 
            virtual void getParam(JsonObject &jsonDat) override;
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat) override;

        protected:

            float startValue_ = -0.5;
            float finalValue_ =  0.5;
            uint64_t duration_ = 2000000;

            void setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setDurationFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);

    };

} // namespace ps

#endif
