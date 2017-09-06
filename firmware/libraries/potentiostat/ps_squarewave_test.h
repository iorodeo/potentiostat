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

            void setWindow(float value);
            float getWindow();

            virtual bool isDone(uint64_t t) const override; 
            virtual uint64_t getDoneTime() const override;
            virtual void reset();

            virtual float getValue(uint64_t t) const override; 
            virtual float getStairValue(uint64_t t) const;
            
            virtual float getMaxValue() const override; 
            virtual float getMinValue() const override; 

            virtual void setSamplePeriod(uint64_t samplePeriod) override;

            virtual bool updateSample(Sample sampleRaw, Sample &sampleTest); 

            virtual void getParam(JsonObject &jsonDat) override;
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat) override;
            
        protected:

            float startValue_ = -0.5;
            float finalValue_ = 0.5;
            float stepValue_ = 0.005;
            float amplitude_ = 0.025;
            float window_ = 0.2;

            float maxValue_ = 0.0;
            float minValue_ = 0.0;
            float stepSign_ = 1.0;

            uint64_t doneTime_ = 0;
            uint64_t halfSamplePeriod_ = 0;
            uint64_t windowLenUs_ = 0; 

            bool isFirst_ = true;
            uint64_t testCnt_ = 0;

            uint64_t numForward_ = 0;
            uint64_t numReverse_ = 0;

            float currForward_ = 0.0;
            float currReverse_ = 0.0;

            void updateDoneTime();
            void updateMaxMinValues();
            void updateWindowLenUs();
            void updateStepSign();

            void setStartValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setFinalValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setStepValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setAmplitudeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setWindowFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
    };


} // namespace ps

#endif
