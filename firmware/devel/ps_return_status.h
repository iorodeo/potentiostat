#ifndef PS_RETURN_STATUS_H
#define PS_RETURN_STATUS_H
#include <Arduino.h>

namespace ps
{

    class ReturnStatus
    {

        public:

            ReturnStatus() {};
            bool success = true;;
            String command;
            String message;
    };

} // namespace ps

#endif
