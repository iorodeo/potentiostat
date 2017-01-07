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
        setVoltGain(DefaultVoltGain);
        setCurrGain(DefaultCurrGain);

        // Initialize analog input/output subsystem
        analogWriteResolution(DefaultAnalogWriteResolution);
        analogReadResolution(DefaultAnalogReadResolution);
        analogReadAveraging(DefaultAnalogReadAveraging);
        analogReference(DefaultAnalogReference);
    }


    void AnalogSubsystem::setVoltGain(VoltGain value)
    {
        switch (value) 
        {
            case VoltGain1X:

                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

            case VoltGain2X:

                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

            case VoltGain5X:

                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            case VoltGain10X:

                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            default:
                break;

        };
    }


    VoltGain AnalogSubsystem::getVoltGain()
    {
        int value0= digitalRead(AD8250_GAIN_A0);
        int value1 = digitalRead(AD8250_GAIN_A1);

        VoltGain volt_gain;  

        if ((value0 == LOW) && (value1 == LOW))
        {
            volt_gain = VoltGain1X;
        }
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            volt_gain =  VoltGain2X;
        }
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            volt_gain = VoltGain5X;
        }
        else
        {
            volt_gain = VoltGain10X;
        }
        return volt_gain;
    }


    void AnalogSubsystem::setCurrGain(CurrGain value)
    {
        switch (value)
        {
            case CurrGainPathIn1:

                digitalWrite(TIA_SW1_IN1,LOW);
                digitalWrite(TIA_SW1_IN2,HIGH);
                digitalWrite(TIA_SW1_IN3,HIGH);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,LOW);
                digitalWrite(TIA_SW2_IN2,HIGH);
                digitalWrite(TIA_SW2_IN3,HIGH);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrGainPathIn2:

                digitalWrite(TIA_SW1_IN1,HIGH);
                digitalWrite(TIA_SW1_IN2,LOW);
                digitalWrite(TIA_SW1_IN3,HIGH);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,HIGH);
                digitalWrite(TIA_SW2_IN2,LOW);
                digitalWrite(TIA_SW2_IN3,HIGH);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrGainPathIn3:

                digitalWrite(TIA_SW1_IN1,HIGH);
                digitalWrite(TIA_SW1_IN2,HIGH);
                digitalWrite(TIA_SW1_IN3,LOW);
                digitalWrite(TIA_SW1_IN4,HIGH);

                digitalWrite(TIA_SW2_IN1,HIGH);
                digitalWrite(TIA_SW2_IN2,HIGH);
                digitalWrite(TIA_SW2_IN3,LOW);
                digitalWrite(TIA_SW2_IN4,HIGH);
                break;

            case CurrGainPathIn4:

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


    CurrGain AnalogSubsystem::getCurrGain()
    {
        int value_sw1_in1 = digitalRead(TIA_SW1_IN1);
        int value_sw1_in2 = digitalRead(TIA_SW1_IN2);
        int value_sw1_in3 = digitalRead(TIA_SW1_IN3);
        int value_sw1_in1 = digitalRead(TIA_SW1_IN4);

        int value_sw2_in1 = digitalRead(TIA_SW2_IN1);
        int value_sw2_in2 = digitalRead(TIA_SW2_IN2);
        int value_sw2_in3 = digitalRead(TIA_SW2_IN3);
        int value_sw2_in1 = digitalRead(TIA_SW2_IN4);

        CurrGain = CurrGainErr;

        // NOT DONE /////


    }

}
