#include "ps_device_id_eeprom.h"
#include <EEPROM.h>

namespace ps
{
    DeviceId_EEPROM::DeviceId_EEPROM(uint32_t address)
    {
        address_ = address;
    }


    ReturnStatus DeviceId_EEPROM::set(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        if (!jsonMsg.containsKey(DeviceIdKey))
        {
            status.success = false;
            status.message = String("json does not contain key: ") + DeviceIdKey;
            return status;
        }

        if (!jsonMsg[DeviceIdKey].is<uint32_t>())
        {
            status.success = false;
            status.message = String("deviceId is not integer");
            return status;
        }

        uint32_t device_id = jsonMsg.get<uint32_t>(DeviceIdKey);
        EEPROM.put(address_,device_id);

        get(jsonDat);

        return status;
    }


    void DeviceId_EEPROM::get(JsonObject &jsonDat)
    {
        uint32_t device_id;
        EEPROM.get(address_,device_id);
        jsonDat.set(DeviceIdKey,device_id);
    }


} // namespace ps
