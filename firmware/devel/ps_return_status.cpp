#include "ps_return_status.h"

namespace ps
{
    void ReturnStatus::appendToMessage(String value)
    {
        if (message.length() > 0)
        {
            message += ", ";
        }
        message += value;
    }

} // namespace ps
