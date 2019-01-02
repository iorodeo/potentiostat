#include "ps_message_sender.h"
#include "ps_time_utils.h"

namespace ps
{

    MessageSender::MessageSender()
    {}

    void MessageSender::sendCommandResponse(ReturnStatus status, JsonObject &jsonDat)
    {
        StaticJsonBuffer<JsonMessageBufferSize> jsonBuffer;
        JsonObject &jsonMsg = jsonBuffer.createObject();
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
        StaticJsonBuffer<JsonMessageBufferSize> jsonBuffer;
        JsonObject &jsonSample = jsonBuffer.createObject();
        jsonSample.set(TimeKey, convertUsToMs(sample.t)); 
        jsonSample.set(VoltKey, sample.volt);
        jsonSample.set(CurrKey, sample.curr);
        if (sample.chan > 0)
        {
            jsonSample.set(ChanKey, sample.chan);
        }
        jsonSample.printTo(Serial);
        Serial.println();
    }

    void MessageSender::sendSampleEnd()
    {
        StaticJsonBuffer<JsonMessageBufferSize> jsonBuffer;
        JsonObject &jsonSample = jsonBuffer.createObject();
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
