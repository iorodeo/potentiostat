#include "ps_electrode_switch.h"
#include "ps_pin_map.h"

#if defined HARDWARE_VERSION_0P2

namespace ps
{
    ElectrodeSwitch::ElectrodeSwitch() {}

    void ElectrodeSwitch::initialize() 
    {
        pinMode(SW_CTR_ELECT, OUTPUT);
        pinMode(SW_REF_ELECT, OUTPUT);
        pinMode(SW_WRK_ELECT, OUTPUT);

    }

    bool ElectrodeSwitch::connected(int pin)
    {
        uint8_t value = digitalRead(pin);
        if (value == HIGH)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void ElectrodeSwitch::setConnected(int pin, bool value)
    {
        if (value)
        {
            digitalWrite(pin, LOW);
        } 
        else
        {
            digitalWrite(pin, HIGH); 
        }
    }


    bool ElectrodeSwitch::ctrConnected()
    {
        return connected(SW_CTR_ELECT);
    }

    void ElectrodeSwitch::setCtrConnected(bool value)
    {
        setConnected(SW_CTR_ELECT,value);
    }

    bool ElectrodeSwitch::refConnected()
    {
        return connected(SW_REF_ELECT);
    }

    void ElectrodeSwitch::setRefConnected(bool value)
    {
        setConnected(SW_REF_ELECT,value);
    }

    bool ElectrodeSwitch::wrkConnected()
    {
        return connected(SW_WRK_ELECT);
    }

    void ElectrodeSwitch::setWrkConnected(bool value)
    {
        setConnected(SW_WRK_ELECT,value);
    }

    bool ElectrodeSwitch::allConnected()
    {
        return ctrConnected() && refConnected() && wrkConnected();
    }

    void ElectrodeSwitch::setAllConnected(bool value)
    {
        setCtrConnected(value);
        setRefConnected(value);
        setWrkConnected(value); 
    }
}

#endif // if defined HARDWARE_VERSION_0P2
