#ifndef PS_MESSAGE_PARSER_H
#define PS_MESSAGE_PARSER_H
#include <Arduino.h>
#include "ArduinoJson.h"
#include "ps_constants.h"

namespace ps
{

    class MessageParser
    {

        public:

            MessageParser();
            JsonObject &parse(String message);

        protected:

            StaticJsonBuffer<JsonBufferSize> jsonBuffer_;

    };

} // namespace ps

#endif
