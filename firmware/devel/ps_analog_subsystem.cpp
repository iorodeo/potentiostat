#include "ps_analog_subsystem.h"

namespace ps
{
    AnalogSubsystem::AnalogSubsystem() {}

    void AnalogSubsystem::initialize()
    {
        // Set mode for DAC gain seletion IO pins
        pinMode(AD8250_GAIN_A0,OUTPUT);
        pinMode(AD8250_GAIN_A1,OUTPUT);

        // Set mode for TIA gain selection IO pins for switch 1
        pinMode(TIA_SW1_IN1,OUTPUT);
        pinMode(TIA_SW1_IN2,OUTPUT);
        pinMode(TIA_SW1_IN3,OUTPUT);
        pinMode(TIA_SW1_IN4,OUTPUT);

        // Set mode for TIA gain selection IO pins for switch 2
        pinMode(TIA_SW2_IN1,OUTPUT);
        pinMode(TIA_SW2_IN2,OUTPUT);
        pinMode(TIA_SW2_IN3,OUTPUT);
        pinMode(TIA_SW2_IN4,OUTPUT);

        // Set to voltage and current range to defaults
        setVoltageRange(DefaultVoltageRange);
        setCurrentRange(DefaultCurrentRange);

        // Initialize analog input/output subsystem
        analogWriteResolution(12);
        analogReadResolution(16);
        analogReadAveraging(16);
        analogReference(INTERNAL);
    }


    void AnalogSubsystem::setVoltageRange(VoltageRange value)
    {
        switch (value) 
        {
            case VoltageRange1V:

                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

            case VoltageRange2V:

                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

            case VoltageRange5V:

                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            case VoltageRange10V:

                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            default:
                break;

        };
    }

    void AnalogSubsystem::setCurrentRange(CurrentRange value)
    {
        switch (value)
        {
            case CurrentRange1uA:

                digitalWrite(TIA_SW1_IN1,LOW);
                digitalWrite(TIA_SW1_IN2,HIGH);
                digitalWrite(TIA_SW1_IN3,HIGH);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,LOW);
                digitalWrite(TIA_SW2_IN2,HIGH);
                digitalWrite(TIA_SW2_IN3,HIGH);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrentRange10uA:

                digitalWrite(TIA_SW1_IN1,HIGH);
                digitalWrite(TIA_SW1_IN2,LOW);
                digitalWrite(TIA_SW1_IN3,HIGH);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,HIGH);
                digitalWrite(TIA_SW2_IN2,LOW);
                digitalWrite(TIA_SW2_IN3,HIGH);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrentRange100uA:

                digitalWrite(TIA_SW1_IN1,HIGH);
                digitalWrite(TIA_SW1_IN2,HIGH);
                digitalWrite(TIA_SW1_IN3,LOW);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,HIGH);
                digitalWrite(TIA_SW2_IN2,HIGH);
                digitalWrite(TIA_SW2_IN3,LOW);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrentRange1000uA:

                digitalWrite(TIA_SW1_IN1,HIGH);
                digitalWrite(TIA_SW1_IN2,HIGH);
                digitalWrite(TIA_SW1_IN3,HIGH);
                digitalWrite(TIA_SW1_IN4,LOW);

                digitalWrite(TIA_SW2_IN1,HIGH);
                digitalWrite(TIA_SW2_IN2,HIGH);
                digitalWrite(TIA_SW2_IN3,HIGH);
                digitalWrite(TIA_SW2_IN4,LOW);
                break;

            default:
                break;

        }
    }

}
