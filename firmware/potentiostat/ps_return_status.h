#ifndef PS_RETURN_STATUS_H
#define PS_RETURN_STATUS_H

#include <Arduino.h>

namespace ps
{

    class ReturnStatus
    {

        public:

            ReturnStatus() { };
            void appendToMessage(String value); 

            bool success = true;;
            String message;

    };


} // namespace ps


#endif
