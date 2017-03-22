#ifndef PS_TIME_UTILS_H
#define PS_TIME_UTILS_H

namespace ps
{

    inline uint32_t convertUsToMs(uint64_t t)
    {
        return uint32_t(t/UINT64_C(1000));
    }


    inline uint64_t convertMsToUs(uint32_t t)
    {
        return uint64_t(t)*UINT64_C(1000);
    }


} // namespace ps

#endif
