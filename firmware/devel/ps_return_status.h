#ifndef PS_RETURN_STATUS_H
#define PS_RETURN_STATUS_H
#include <Arduino.h>
#include "ArduinoJson.h"

namespace ps
{

    class ReturnStatus
    {

        public:

            ReturnStatus() { };
            bool success = true;;
            String command;
            String message;

        protected:

            StaticJsonBuffer<JsonMessageBufferSize> jsonBuffer_;
            JsonObject *jsonDataPtr_ = nullptr;

    };

} // namespace ps



#endif
