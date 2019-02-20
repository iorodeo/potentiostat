#ifndef PS_MESSAGE_PARSER_H
#define PS_MESSAGE_PARSER_H

#include <Arduino.h>
#include "ps_constants.h"

#include "third-party/ArduinoJson/ArduinoJson.h"

namespace ps
{

    class MessageParser
    {

        public:

            MessageParser();
            JsonObject& parse(String &message, StaticJsonBuffer<JsonMessageBufferSize> &jsonBuffer);

    };

} // namespace ps

#endif
