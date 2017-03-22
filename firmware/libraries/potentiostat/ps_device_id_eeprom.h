#ifndef PS_DEVICE_ID_EEPROM_H
#define PS_DEVICE_ID_EEPROM_H

#include "ps_constants.h"
#include "ps_return_status.h"

#include "third-party/ArduinoJson/ArduinoJson.h"

namespace ps
{

    class DeviceId_EEPROM
    {

        public:

            DeviceId_EEPROM(uint32_t address=EEPROM_DeviceIdAddress);
            ReturnStatus set(JsonObject &jsonMsg, JsonObject &jsonDat);
            void get(JsonObject &jsonDat);

        protected:

            uint32_t address_;

    };

} // namespace ps

#endif 
