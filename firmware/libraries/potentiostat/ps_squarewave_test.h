#ifndef PS_SQUAREWAVE_TEST_H
#define PS_SQUAREWAVE_TEST_H
#include "ps_base_test.h"

namespace ps 
{
    class SquareWaveTest : public BaseTest
    {
        public:

            SquareWaveTest();

            void setStartValue(float value);
            float getStartValue();

            void setFinalValue(float value);
            float getFinalValue();

            void setStepValue(float value);
            float getStepValue();

            void setAmplitude(float value);
            float getAmplitude();

            // -------------------------------------------------------------------
            // TODO: need to insure setPeriod gets called if sample rate changes
            // -------------------------------------------------------------------
            void setPeriod(uint64_t duration);
            uint64_t getPeriod();

            virtual bool isDone(uint64_t t) const override; 
            virtual uint64_t getDoneTime() const override;

            // -------------------------------------------------------------------
            // TODO: implement get value method 
            // -------------------------------------------------------------------
            //virtual float getValue(uint64_t t) const override; 
            
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 

            virtual void getParam(JsonObject &jsonDat) override;
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat) override;

        protected:

            float startValue_ = -0.5;
            float finalValue_ = 0.5;
            float stepValue_ = 0.005;
            float amplitude_ = 0.025;
            uint64_t period_ = 25000;

            uint64_t doneTime_ = 0;
            void updateDoneTime();

            void setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setStepValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setAmplitudeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setPeriodFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
    };

} // namespace ps

#endif
