#include "ps_message_parser.h"

namespace ps
{ 
    MessageParser::MessageParser()
    { }

    JsonObject &MessageParser::parse(String &message, StaticJsonBuffer<JsonMessageBufferSize> &jsonBuffer)
    { 
        return jsonBuffer.parseObject((char *)(message.c_str()));
    }

} // namespace ps
