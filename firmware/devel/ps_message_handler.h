#ifndef PS_MESSAGE_HANDLER_H
#define PS_MESSAGE_HANDLER_H
#include <Arduino.h>
#include "ps_constants.h"
#include "ps_circular_buffer.h"

namespace ps
{

    class MessageHandler
    {

        public:

            MessageHandler();
            void reset();
            void readData();
            String next();
            bool available() const;
            uint32_t getMessageCnt() const;
            uint32_t getTotalMessageCnt() const;

        protected:

            CircularBuffer<char,SerialBufferSize> serialBuffer_;
            bool overflow_ = false;
            uint32_t messageCnt_ = 0;
            uint32_t totalMessageCnt_ = 0;


    };

} // namespace ps

#endif
