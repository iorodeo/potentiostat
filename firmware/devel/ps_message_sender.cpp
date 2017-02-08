#include "ps_message_sender.h"

namespace ps
{

    MessageSender::MessageSender()
    {}

    void MessageSender::sendCommandResponse(ReturnStatus status)
    {
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonRoot = jsonBuffer_.createObject();

        jsonRoot["success"] = status.success;
        jsonRoot["message"] = status.message;
        jsonRoot["command"] = status.command;

        jsonRoot.printTo(Serial);
        Serial.println();

    }

    void MessageSender::sendSample(Sample sample)
    {
        jsonBuffer_ = StaticJsonBuffer<JsonMessageBufferSize>(); 
        JsonObject &jsonRoot = jsonBuffer_.createObject();

        // Send time in us as string
        // -------------------------------------------------------
        //char timeBuf[100]; 
        //snprintf(timeBuf,sizeof(timeBuf),"%llu", sample.t);
        //jsonRoot["t"] = timeBuf;
        // ------------------------------------------------------

        jsonRoot.set("t",uint32_t(sample.t/1000)); // send time in ms
        jsonRoot.set("v",sample.volt,5);
        jsonRoot.set("i",sample.curr,5);

        jsonRoot.printTo(Serial);
        Serial.println();
    }


} // namespace ps

