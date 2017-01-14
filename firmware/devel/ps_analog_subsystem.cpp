#include "ps_analog_subsystem.h"

namespace ps
{
    // AnalogSubsystem public methods
    // --------------------------------------------------------------------------------------------
    
    const VoltRange AnalogSubsystem::DefaultVoltRange = VoltRangeVector[0]; 
    const CurrRange AnalogSubsystem::DefaultCurrRange = CurrRangeVector[1]; 

    AnalogSubsystem::AnalogSubsystem() {}

    void AnalogSubsystem::initialize()
    {
        // Setup analog subsystem. This method must be called (typically setup)
        // before the AnalogSubsystem can be used. 
        
        // Set  Dac gain seletion IO pins to output
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
        setVoltRange(DefaultVoltRange);
        setCurrRange(DefaultCurrRange);

        // Initialize analog input/output subsystem
        analogWriteResolution(DefaultAnalogWriteResolution);
        analogReadResolution(DefaultAnalogReadResolution);
        analogReadAveraging(DefaultAnalogReadAveraging);
        analogReference(DefaultAnalogReference);

        // Set output voltage to zero
        setValueDac(MidValueDac); 
    
    }


    void AnalogSubsystem::setVolt(float value) 
    {
        // Set working to reference electrode (output) voltage
        setValueDac(voltRange_.valueToInt(value));
    }


    float AnalogSubsystem::getVolt() const     
    {
        // Get working to reference electrode (output) voltage setting
        return voltRange_.intToValue(valueDac_);
    }


    float AnalogSubsystem::getCurr() const           
    {
        // Get current measurement from working electrode
        return currRange_.intToValue(getTransAmpAin());
    }


    float AnalogSubsystem::getRefElectVolt() const   
    {
        // Get measurement of reference electrode voltage (primarily for debugging)
        return VoltRange10V.intToValue(getRefElectAin());
    }


    void AnalogSubsystem::setVoltRange(VoltRange range)
    {
        // Set the output voltage range - for working to reference electrode voltage
        // Note, this command will change the VoltGain setting. 
        voltRange_ = range;
        setVoltGain(voltRange_.gain());
    }


    VoltRange AnalogSubsystem::getVoltRange() const
    { 
        // Returns the devices voltage range settings.
        return voltRange_;
    }


    void AnalogSubsystem::setCurrRange(CurrRange range)
    {
        // Set current transimpedance amplifiers current range
        setCurrGainPath(currRange_.gain());
    }


    CurrRange AnalogSubsystem::getCurrRange() const
    {
        // Returns the transimpedance amplifier's current range setting 
        return currRange_;
    }


    String AnalogSubsystem::getVoltRangeName() const
    { 
        // Returns a string representation of the voltage range setting
        return voltRange_.name();
    }


    String AnalogSubsystem::getCurrRangeName() const
    {
        // Returns a string representation of the current range
        return currRange_.name();
    }


    // AnalogSubsystem protected methods
    // --------------------------------------------------------------------------------------------

    void AnalogSubsystem::setVoltGain(VoltGain value)
    {
        // Sets the amplifier gain for the working to reference electrode voltage output

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

        }
    }


    VoltGain AnalogSubsystem::getVoltGain() const
    {
        // Returns the value for the gain (as currently set) for output voltage amplifier
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


    void AnalogSubsystem::setCurrGainPath(CurrGainPath value)
    {
        // Sets the gain path (In1,In2,In3,In4) used for transimpedence amplifier
       
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


    CurrGainPath AnalogSubsystem::getCurrGainPath() const
    {
        // Returns the gain path setting (currently in use) by the transimpedance
        // amplifier

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

        CurrGainPath currGainPath = CurrGainPathErr;

        if ((sw1 == 0b1110 ) && (sw2 == 0b1110))
        {
            currGainPath = CurrGainPathIn1;
        }
        else if ((sw1 == 0b1101) && (sw2 == 0b1101))
        {
            currGainPath = CurrGainPathIn2;
        }
        else if ((sw1 == 0b1011) && (sw2 == 0b1011))
        {
            currGainPath = CurrGainPathIn3;
        }
        else if ((sw1 == 0b0111) & (sw2 == 0b0111))
        {
            currGainPath = CurrGainPathIn4;
        }
        return currGainPath;
    }

    String AnalogSubsystem::getVoltGainString() const
    {
        // Returns a string representation for voltage gain
        VoltGain voltGain = getVoltGain();
        return voltGainToString(voltGain);
    }


    String AnalogSubsystem::getCurrGainPathString() const
    {
        // Returns a string representation for current gain path
        CurrGainPath currGainPath = getCurrGainPath();
        return currGainPathToString(currGainPath);
    }


    void AnalogSubsystem::setValueDac(uint16_t value)
    {
        // The value of the output voltage Dac
        valueDac_ = min(value,MaxValueDac);
        analogWrite(DAC_UNI_PIN,valueDac_);
    }


    uint16_t AnalogSubsystem::getValueDac() const
    {
        // Return the value currently used by the output voltage Dac
        return valueDac_;
    }


    uint16_t AnalogSubsystem::getTransAmpAin() const  
    {
        // Read analog input associated with the transimpedance amplifier 
       return analogRead(TIA_OUT_UNI_PIN);
    }


    uint16_t AnalogSubsystem::getRefElectAin() const
    {
        // Read analog input associated with the refernce electrode
        return analogRead(REF_ELECT_UNI_PIN);
    }


} // namespace ps
