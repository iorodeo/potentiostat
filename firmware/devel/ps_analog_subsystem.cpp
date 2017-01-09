#include "ps_analog_subsystem.h"

namespace ps
{
    AnalogSubsystem::AnalogSubsystem() {}


    void AnalogSubsystem::initialize()
    {
        // Set  DAC gain seletion IO pins to output
        pinMode(AD8250_GAIN_A0,OUTPUT);
        pinMode(AD8250_GAIN_A1,OUTPUT);

        // Set TIA (current) gain selection IO pins for switch 1 to output
        pinMode(TIA_SW1_IN1,OUTPUT);
        pinMode(TIA_SW1_IN2,OUTPUT);
        pinMode(TIA_SW1_IN3,OUTPUT);
        pinMode(TIA_SW1_IN4,OUTPUT);

        // Set TIA (current) gain selection IO pins for switch 2 to output
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

        // Set output voltage to zero
        setValueDAC(MidValueDAC); 
    
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


    VoltGain AnalogSubsystem::getVoltGain() const
    {
        uint8_t value0 = digitalRead(AD8250_GAIN_A0);
        uint8_t  value1 = digitalRead(AD8250_GAIN_A1);

        VoltGain voltGain;  

        if ((value0 == LOW) && (value1 == LOW))
        {
            voltGain = VoltGain1X;
        }
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            voltGain =  VoltGain2X;
        }
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            voltGain = VoltGain5X;
        }
        else
        {
            voltGain = VoltGain10X;
        }
        return voltGain;
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


    CurrGain AnalogSubsystem::getCurrGain() const
    {
        uint8_t sw1 = 0;
        sw1 += digitalRead(TIA_SW1_IN1) << 0;
        sw1 += digitalRead(TIA_SW1_IN2) << 1;
        sw1 += digitalRead(TIA_SW1_IN3) << 2;
        sw1 += digitalRead(TIA_SW1_IN4) << 3;

        uint8_t sw2 = 0;
        sw2 += digitalRead(TIA_SW2_IN1) << 0;
        sw2 += digitalRead(TIA_SW2_IN2) << 1;
        sw2 += digitalRead(TIA_SW2_IN3) << 2;
        sw2 += digitalRead(TIA_SW2_IN4) << 3;

        CurrGain currGain = CurrGainPathErr;

        if ((sw1 == 0b1110 ) && (sw2 == 0b1110))
        {
            currGain = CurrGainPathIn1;
        }
        else if ((sw1 == 0b1101) && (sw2 == 0b1101))
        {
            currGain = CurrGainPathIn2;
        }
        else if ((sw1 == 0b1011) && (sw2 == 0b1011))
        {
            currGain = CurrGainPathIn3;
        }
        else if ((sw1 == 0b0111) & (sw2 == 0b0111))
        {
            currGain = CurrGainPathIn4;
        }
        return currGain;
    }

    String AnalogSubsystem::getVoltGainString() const
    {
        VoltGain voltGain = getVoltGain();
        return voltGainToString(voltGain);
    }


    String AnalogSubsystem::getCurrGainString() const
    {
        CurrGain currGain = getCurrGain();
        return currGainToString(currGain);
    }


    void AnalogSubsystem::setValueDAC(uint16_t value)
    {
        valueDAC_ = min(value,MaxValueDAC);
        analogWrite(DAC_UNI_PIN,valueDAC_);
    }


    uint16_t AnalogSubsystem::getValueDAC() const
    {
        return valueDAC_;
    }


    uint16_t AnalogSubsystem::getTransAmpAin() const  
    {
       return analogRead(TIA_OUT_UNI_PIN);
    }


    uint16_t AnalogSubsystem::getRefElectAin() const
    {
        return analogRead(REF_ELECT_UNI_PIN);
    }

}
