#ifndef PS_MESSAGE_SENDER_H
#define PS_MESSAGE_SENDER_H

#include <Arduino.h>
#include "ps_constants.h"
#include "ps_sample.h"
#include "ps_return_status.h"

#include "third-party/ArduinoJson/ArduinoJson.h"

namespace ps
{

    class MessageSender
    {

        public:

            MessageSender();
            void sendSample(Sample sample);
            void sendSampleEnd();
            void sendCommandResponse(ReturnStatus status, JsonObject &jsonDat);

    };


} // namespace ps


#endif
