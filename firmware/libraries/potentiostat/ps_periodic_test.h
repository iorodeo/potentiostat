#ifndef PS_PERIODIC_TEST_H
#define PS_PERIODIC_TEST_H

#include "ps_base_test.h"
#include "ps_constants.h"

namespace ps
{

    class PeriodicTest : public BaseTest
    {
        public:

            static constexpr float DefaultAmplitude = 1.0; 
            static constexpr float DefaultOffset = 0.0; 
            static constexpr float DefaultShift = 0.0;
            static constexpr uint64_t DefaultPeriod = UINT64_C(1000000);
            static constexpr uint32_t DefaultNumCycles = UINT32_C(10);

            PeriodicTest();

            virtual void setAmplitude(float amplitude);
            virtual float getAmplitude() const;

            virtual void setOffset(float offset);
            virtual float getOffset() const;

            virtual void setPeriod(uint64_t period);
            virtual uint64_t getPeriod() const;

            virtual void setNumCycles(uint32_t numCycles);
            virtual uint32_t getNumCycles() const;

            virtual void setShift(float lag);
            virtual float getShift() const;

            virtual uint32_t getCycleCount(uint64_t t) const;

            virtual bool isDone(uint64_t t) const override;
            virtual uint64_t getDoneTime() const override;
            virtual float getValue(uint64_t t) const override;
            virtual float getMaxValue() const override;
            virtual float getMinValue() const override;
            virtual void getParam(JsonObject &jsonDat) override;
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat) override;

        protected:

            float amplitude_ = DefaultAmplitude;     // 12-bit Dac int
            float offset_ = DefaultOffset;           // 12-bit Dac int
            uint64_t period_ = DefaultPeriod;        // Waveform period (us)
            uint32_t numCycles_ = DefaultNumCycles;  // Number of cycles to perform

            float shift_ = DefaultShift;             // Waveform shift as fraction of period [0,1]
            uint64_t shiftInUs_ = 0;                 // Waveform shift in us;
            
            void setAmplitudeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setOffsetFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setPeriodFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setNumCyclesFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setShiftFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);

            void updateShiftInUs();




    };


}

#endif
