#include "ps_message_sender.h"
#include "ps_time_utils.h"

namespace ps
{

    MessageSender::MessageSender()
    {}

    void MessageSender::sendCommandResponse(ReturnStatus status, JsonObject &jsonDat)
    {
        // ArduinoJson upgrade
        // ----------------------------------------------------
        //jsonBuffer_.clear(); 
        // ----------------------------------------------------
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonMsg = jsonBuffer_.createObject();

        jsonMsg.set(SuccessKey, status.success);
        if (status.message.length() > 0)
        {
            jsonMsg.set(MessageKey, status.message);
        }
        jsonMsg.set(ResponseKey, jsonDat);


        jsonMsg.printTo(Serial);
        Serial.println();

    }

    void MessageSender::sendSample(Sample sample)
    {
        // ArduinoJson upgrade
        // ----------------------------------------------------
        //jsonBuffer_.clear(); 
        // ----------------------------------------------------
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonSample = jsonBuffer_.createObject();

        jsonSample.set(TimeKey, convertUsToMs(sample.t)); 
        jsonSample.set(VoltKey, sample.volt,JsonFloatDecimals);
        jsonSample.set(CurrKey, sample.curr,JsonFloatDecimals);

        jsonSample.printTo(Serial);
        Serial.println();
    }

    void MessageSender::sendSampleEnd()
    {
        // ArduinoJson upgrade
        // ----------------------------------------------------
        //jsonBuffer_.clear(); 
        // ----------------------------------------------------
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonSample = jsonBuffer_.createObject();
        jsonSample.printTo(Serial);
        Serial.println();
    }

} // namespace ps


// Send time in us as string
// -------------------------------------------------------
//char timeBuf[100]; 
//snprintf(timeBuf,sizeof(timeBuf),"%llu", sample.t);
//jsonRoot[TimeKey] = timeBuf;
// ------------------------------------------------------
