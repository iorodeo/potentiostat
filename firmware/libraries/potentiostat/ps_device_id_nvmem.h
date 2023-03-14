#ifndef PS_DEVICE_ID_NVMEM_H
#define PS_DEVICE_ID_NVMEM_H
#include "ps_constants.h"
#include "ps_return_status.h"
#include "ArduinoJson.h"

namespace ps
{

    class DeviceId_NVMEM
    {

        public:
#if defined DEVBOARD_TEENSY
            DeviceId_NVMEM(uint32_t address=EEPROM_DeviceIdAddress);
#elif defined DEVBOARD_ITSY_BITSY
            DeviceId_NVMEM();
#endif
            ReturnStatus set(JsonObject &jsonMsg, JsonObject &jsonDat);
            void get(JsonObject &jsonDat);

#if defined DEVBOARD_TEENSY
        protected:
            uint32_t address_;
#endif

    };

} // namespace ps

#endif 
