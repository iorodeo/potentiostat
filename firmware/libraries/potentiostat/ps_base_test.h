#ifndef PS_BASE_TEST_H
#define PS_BASE_TEST_H
#include <Arduino.h>
#include "ArduinoJson.h"
#include "ps_return_status.h"

namespace ps
{

    class BaseTest
    {

        public:

            BaseTest();

            virtual bool isDone(uint64_t t) const; 
            virtual uint64_t getDoneTime() const;
            virtual void reset();

            virtual float getValue(uint64_t t) const; 
            virtual float getMaxValue() const; 
            virtual float getMinValue() const; 

            virtual void setQuietTime(uint64_t quietTime);
            virtual uint64_t getQuietTime() const;

            virtual void setQuietValue(float value);
            virtual void setQuietValueToStart();
            virtual float getQuietValue() const;

            virtual void setName(String name);
            virtual String getName();


            virtual void getParam(JsonObject &jsonDat);
            virtual ReturnStatus setParam(JsonObject &jsonMsg, JsonObject &jsonDat);

        protected:

            uint64_t quietTime_ = 0;
            float quietValue_ = 0.0;
            String name_ = String("base");

            JsonObject &getParamJsonObject(JsonObject &json, ReturnStatus &status);
            void setQuietValueFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);
            void setQuietTimeFromJson(JsonObject &jsonMsgPrm, JsonObject &jsonDatPrm, ReturnStatus &status);


    };

}

#endif
