#include "ps_message_parser.h"

namespace ps
{ 
    MessageParser::MessageParser()
    { }

    JsonObject &MessageParser::parse(String &message)
    { 
        // Clear the buffer and parse the message
        jsonBuffer_ = StaticJsonBuffer<JsonBufferSize>(); 
        return jsonBuffer_.parseObject((char *)(message.c_str()));
    }

} // namespace ps
