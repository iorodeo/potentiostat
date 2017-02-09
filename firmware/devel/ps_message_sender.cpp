#include "ps_message_sender.h"
#include "ps_time_utils.h"

namespace ps
{

    MessageSender::MessageSender()
    {}


    void MessageSender::sendCommandResponse(ReturnStatus status, JsonObject &jsonDat)
    {
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonMsg = jsonBuffer_.createObject();

        //JsonArray &array = jsonDat.createNestedArray("array");
        //array.add(1);
        //array.add(2);
        //array.add(3);
        

        jsonMsg.set("success", status.success);
        if (status.message.length() > 0)
        {
            jsonMsg.set("message", status.message);
        }
        jsonMsg.set("response", jsonDat);


        jsonMsg.printTo(Serial);
        Serial.println();

    }


    void MessageSender::sendSample(Sample sample)
    {
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonSample = jsonBuffer_.createObject();

        jsonSample.set("t",convertUsToMs(sample.t)); 
        jsonSample.set("v",sample.volt,JsonFloatDecimals);
        jsonSample.set("i",sample.curr,JsonFloatDecimals);

        jsonSample.printTo(Serial);
        Serial.println();
    }


} // namespace ps


// Send time in us as string
// -------------------------------------------------------
//char timeBuf[100]; 
//snprintf(timeBuf,sizeof(timeBuf),"%llu", sample.t);
//jsonRoot["t"] = timeBuf;
// ------------------------------------------------------
