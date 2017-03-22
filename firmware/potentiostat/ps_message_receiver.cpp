#include "ps_message_receiver.h"
#include <util/atomic.h>

namespace ps
{
    MessageReceiver::MessageReceiver() 
    { }

    void MessageReceiver::reset()
    {
        overflow_ = false;
        messageCnt_ = 0;
    }


    void MessageReceiver::readData()
    {
        while(Serial.available() > 0)
        {
            char byte = Serial.read();
            if (!serialBuffer_.full())
            {
                serialBuffer_.push_back(byte);
                if (byte == '\n')
                {
                    messageCnt_++;
                    totalMessageCnt_++;
                }
            }
            else
            {
                overflow_ = true;
            }
        }
    }


    String MessageReceiver::next()
    {
        String message("");
        if (messageCnt_ > 0)
        {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
            {   
                while (!serialBuffer_.empty())
                {
                    char byte = serialBuffer_.front();
                    serialBuffer_.pop_front();
                    if (byte == '\n')
                    {
                        break;
                    }
                    message += String(byte);
                }
                messageCnt_--;
            }
        }
        return message;
    }


    bool MessageReceiver::available() const
    {
        return (messageCnt_ > 0);
    }


    uint32_t MessageReceiver::getMessageCnt() const
    {
        return messageCnt_;
    }


    uint32_t MessageReceiver::getTotalMessageCnt() const
    {
        return totalMessageCnt_;
    }


} // namespace ps
