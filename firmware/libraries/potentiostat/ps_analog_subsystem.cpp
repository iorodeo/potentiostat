#include "ps_analog_subsystem.h"
#include "ps_constants.h"

namespace ps
{
    // AnalogSubsystem public methods
    // --------------------------------------------------------------------------------------------

    AnalogSubsystem::AnalogSubsystem() {}

    void AnalogSubsystem::initialize()
    {
        // Setup analog subsystem. This method must be called (typically setup)
        // before the AnalogSubsystem can be used. 
        
#if defined HARDWARE_VERSION_0P1   
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
#elif defined HARDWARE_VERSION_0P2
        // Set  DAC and TIA gain seletion pins to output
        pinMode(DAC_GAIN_A0,OUTPUT);
        pinMode(DAC_GAIN_A1,OUTPUT);
        pinMode(TIA_GAIN_A0,OUTPUT);
        pinMode(TIA_GAIN_A1,OUTPUT);
        pinMode(REF_GAIN_A0,OUTPUT);
        pinMode(REF_GAIN_A1,OUTPUT);
#else
#   error "HARDWARE_VERSION must be specified"
#endif

        // Set to voltage and current range to defaults
        setVoltRange(VoltRangeDac1V);
#if defined HARDWARE_VERSION_0P1   
        refElectVoltRange_ = VoltRangeAdc10V;
#elif defined HARDWARE_VERSION_0P2
        setRefElectVoltRange(VoltRangeAdc1V);
#else
#   error "HARDWARE_VERSION must be specified"
#endif

#if defined CURRENT_VARIANT_MICRO_AMP
        setCurrRange(CurrRange10uA);
#elif defined CURRENT_VARIANT_NANO_AMP
        setCurrRange(CurrRange10uA);
#elif defined CURRENT_VARIANT_MILL_AMP
        setCurrRange(CurrRange1000uA);
#else
#   error "CURRENT_VARIANT must be specified"
#endif
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
        setValueDac(voltRange_.valueToInt(SignDac*value));
    }


    float AnalogSubsystem::getVolt() const     
    {
        // Get working to reference electrode (output) voltage setting
        return SignDac*voltRange_.intToValue(valueDac_);
    }


    float AnalogSubsystem::getCurr() const           
    {
        // Get current measurement from working electrode
        return SignCurr*currRange_.intToValue(getTransAmpAin());
    }


    float AnalogSubsystem::getRefElectVolt() const   
    {
        // Get measurement of reference electrode voltage 
        return SignAdc*refElectVoltRange_.intToValue(getRefElectAin());
    }


    void AnalogSubsystem::setVoltRange(VoltRangeDac range)
    {
        // Set the output voltage range - for working to reference electrode voltage
        // Note, this command will change the VoltGain setting. 
        voltRange_ = range;
        setVoltGain(voltRange_.gain());
    }

    
    bool AnalogSubsystem::autoVoltRange(float minVolt, float maxVolt)
    {
        bool success = false;

        VoltRangeDac bestRange;
        float bestDelta;

        for (size_t i=0; i<VoltRangeDacArray.size(); i++)
        {
            VoltRangeDac range = VoltRangeDacArray[i];
            float minRange = range.minValue();
            float maxRange = range.maxValue();
            if ((minVolt >= minRange) && (maxVolt <= maxRange))
            {
                float delta = max(minVolt - minRange, maxRange - maxVolt);
                if (success)
                {
                    if (delta < bestDelta)
                    {
                        bestRange = range;
                        bestDelta = delta;
                    }
                }
                else
                {
                    bestRange = range;
                    bestDelta = delta;
                    success = true;
                }
            }
        }
        if (success)
        {
            setVoltRange(bestRange);
        }
        return success;
    }


    VoltRangeDac AnalogSubsystem::getVoltRange() const
    { 
        // Returns the device's voltage range setting.
        return voltRange_;
    }


    void AnalogSubsystem::setCurrRange(CurrRange range)
    {
        // Set current transimpedance amplifiers current range
        currRange_ = range;
        setCurrGainPath(currRange_.gain());
    }


    CurrRange AnalogSubsystem::getCurrRange() const
    {
        // Returns the transimpedance amplifier's current range setting 
        return currRange_;
    }


    ReturnStatus AnalogSubsystem::setVoltRangeByName(String voltRangeName)
    {
        ReturnStatus status;
        bool found = false;
        for (size_t i=0; i<VoltRangeDacArray.size(); i++)
        {
            if (voltRangeName.equals(VoltRangeDacArray[i].name()))
            {
                found = true;
                setVoltRange(VoltRangeDacArray[i]);
            }
        }
        if (!found)
        {
            status.success = false;
            status.message = String("voltRange, ") + voltRangeName + String(", not found");
        }
        return status;
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

    ReturnStatus AnalogSubsystem::setCurrRangeByName(String currRangeName)
    {
        ReturnStatus status;
        bool found = false;

        for (size_t i=0; i<CurrRangeArray.size(); i++)
        {
            if (currRangeName.equals(CurrRangeArray[i].name()))
            {
                found = true;
                setCurrRange(CurrRangeArray[i]);
            }
        }
        
        if (!found)
        {
            status.success = false;
            status.message = String("currRange, ") + currRangeName + String(", not found");
        }
        return status;
    }

#if defined HARDWARE_VERSION_0P2 
    void AnalogSubsystem::setRefElectVoltRange(VoltRangeAdc range)
    {
        // Set the voltage range for working to reference electrode analog input 
        refElectVoltRange_ = range;
        setRefElectVoltGain(refElectVoltRange_.gain());
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    VoltRangeAdc AnalogSubsystem::getRefElectVoltRange() const
    {
        // Returns the device's reference electrode voltage range setting
        return refElectVoltRange_;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    ReturnStatus AnalogSubsystem::setRefElectVoltRangeByName(String voltRangeName)
    {
        ReturnStatus status;
        bool found = false;
        for (size_t i=0; i<VoltRangeAdcArray.size(); i++)
        {
            if (voltRangeName.equals(VoltRangeAdcArray[i].name()))
            {
                found = true;
                setRefElectVoltRange(VoltRangeAdcArray[i]);
            }
        }
        if (!found)
        {
            status.success = false;
            status.message = String("voltRange, ") + voltRangeName + String(", not found");
        }
        return status;
    }
#endif

#if defined HARDWARE_VERSION_0P2 
    String AnalogSubsystem::getRefElectVoltRangeName() const
    {
        // Returns a string representation of the reference electrode voltage range setting
        return refElectVoltRange_.name();
    }
#endif

#if defined HARDWARE_VERSION_0P2
    bool AnalogSubsystem::autoRefElectVoltRange(float minVolt, float maxVolt)
    {
        bool success = false;

        VoltRangeAdc bestRange;
        float bestDelta;

        for (size_t i=0; i<VoltRangeAdcArray.size(); i++)
        {
            VoltRangeAdc range = VoltRangeAdcArray[i];
            float minRange = range.minValue();
            float maxRange = range.maxValue();
            if ((minVolt >= minRange) && (maxVolt <= maxRange))
            {
                float delta = max(minVolt - minRange, maxRange - maxVolt);
                if (success)
                {
                    if (delta < bestDelta)
                    {
                        bestRange = range;
                        bestDelta = delta;
                    }
                }
                else
                {
                    bestRange = range;
                    bestDelta = delta;
                    success = true;
                }
            }
        }
        if (success)
        {
            setRefElectVoltRange(bestRange);
        }
        return success;
    }
#endif

    // AnalogSubsystem protected methods
    // --------------------------------------------------------------------------------------------

    void AnalogSubsystem::setVoltGain(VoltGain value)
    {
        // Sets the amplifier gain for the working to reference electrode voltage output

        switch (value) 
        {
#if defined HARDWARE_VERSION_0P1
            case VoltGain1X:
                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

            case VoltGain2X:
                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,LOW);
                break;

#if defined VOLTAGE_VARIANT_AD8250 
            case VoltGain5X:
                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            case VoltGain10X:
                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

#elif defined VOLTAGE_VARIANT_AD8251
            case VoltGain4X:
                digitalWrite(AD8250_GAIN_A0,LOW);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;

            case VoltGain8X:
                digitalWrite(AD8250_GAIN_A0,HIGH);
                digitalWrite(AD8250_GAIN_A1,HIGH);
                break;
#else
#   error "VOLTAGE_VARIANT must be AD8250 of AD8251 for hardware version 0.1"
#endif // #if defined VOLTAGE_VARIANT 

#elif defined HARDWARE_VERSION_0P2
#if defined VOLTAGE_VARIANT_10V
            case VoltGain1X:
                digitalWrite(DAC_GAIN_A0,LOW);
                digitalWrite(DAC_GAIN_A1,LOW);
                break;

            case VoltGain2X:
                digitalWrite(DAC_GAIN_A0,HIGH);
                digitalWrite(DAC_GAIN_A1,LOW);
                break;

            case VoltGain5X:
                digitalWrite(DAC_GAIN_A0,LOW);
                digitalWrite(DAC_GAIN_A1,HIGH);
                break;

            case VoltGain10X:
                digitalWrite(DAC_GAIN_A0,HIGH);
                digitalWrite(DAC_GAIN_A1,HIGH);
                break;
#else
#   error "VOLTAGE_VARIANT must be 10V for hardware version 0.1"
#endif // #if defined VOLTAGE_VARIANT

#else
#   error "HARDWARE_VERSION must be specified"
#endif // #if defined HARDWARE_VERSION
            default:
                break;

        } // switch (value)

    }  // void AnalogSubsystem::setVoltGain


    VoltGain AnalogSubsystem::getVoltGain() const
    {
        // Returns the value for the gain (as currently set) for output voltage amplifier
#if defined HARDWARE_VERSION_0P1
        uint8_t value0 = digitalRead(AD8250_GAIN_A0);
        uint8_t  value1 = digitalRead(AD8250_GAIN_A1);
#elif defined HARDWARE_VERSION_0P2
        uint8_t value0 = digitalRead(DAC_GAIN_A0);
        uint8_t  value1 = digitalRead(DAC_GAIN_A1);
#else
#   error "HARDWARE_VERSION must be specified"
#endif
        VoltGain voltGain;  

        if ((value0 == LOW) && (value1 == LOW))
        {
            voltGain = VoltGain1X;
        }
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            voltGain =  VoltGain2X;
        }
#if defined(VOLTAGE_VARIANT_AD8250) || defined(VOLTAGE_VARIANT_10V)
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            voltGain = VoltGain5X;
        }
        else
        {
            voltGain = VoltGain10X;
        }
#elif defined VOLTAGE_VARIANT_AD8251
        else if ((value0 == HIGH) && (value1 == LOW))
        {
            voltGain = VoltGain4X;
        }
        else
        {
            voltGain = VoltGain8X;
        }
#else
#   error "VOLTAGE_VARIANT must be specified"
#endif
        return voltGain;
    }


    void AnalogSubsystem::setCurrGainPath(CurrGainPath value)
    {
        // Sets the gain path (In1,In2,In3,In4) used for transimpedence amplifier
       
        switch (value)
        {
#if defined HARDWARE_VERSION_0P1
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
#elif defined HARDWARE_VERSION_0P2
            case CurrGainPathIn1:
                digitalWrite(TIA_GAIN_A0,LOW);
                digitalWrite(TIA_GAIN_A1,LOW);
                break;

            case CurrGainPathIn2:
                digitalWrite(TIA_GAIN_A0,HIGH);
                digitalWrite(TIA_GAIN_A1,LOW);
                break;

            case CurrGainPathIn3:
                digitalWrite(TIA_GAIN_A0,LOW);
                digitalWrite(TIA_GAIN_A1,HIGH);
                break;

            case CurrGainPathIn4:
                digitalWrite(TIA_GAIN_A0,HIGH);
                digitalWrite(TIA_GAIN_A1,HIGH);
                break;
#else
#   error "HARDWARE_VERSION must be specified"
#endif 
            default:
                break;

        }
    }


    CurrGainPath AnalogSubsystem::getCurrGainPath() const
    {
        // Returns the gain path setting (currently in use) by the transimpedance 
        // amplifier
        CurrGainPath currGainPath = CurrGainPathErr;
        
#if defined HARDWARE_VERSION_0P1
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
#elif defined HARDWARE_VERSION_0P2
        uint8_t a0 = digitalRead(TIA_GAIN_A0);
        uint8_t a1 = digitalRead(TIA_GAIN_A1);

        if ((a0 == LOW) && (a1 == LOW)) 
        {
            currGainPath = CurrGainPathIn1;
        }
        else if ((a0 == HIGH) && (a1 == LOW))
        {
            currGainPath = CurrGainPathIn2;
        }
        else if ((a0 == LOW) && (a1 == HIGH))
        {
            currGainPath = CurrGainPathIn3;
        }
        else if ((a0 == HIGH) && (a1 == HIGH))
        {
            currGainPath = CurrGainPathIn4;
        }
#else
#   error "HARDWARE_VERSION must be defined"
#endif
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

#if defined HARDWARE_VERSION_0P2
    void AnalogSubsystem::setRefElectVoltGain(VoltGain value)
    {
        // Sets the amplifier gain for the reference electrode voltage 
        // analog input 
        switch (value) 
        {
            case VoltGain1X:
                digitalWrite(REF_GAIN_A0,LOW);
                digitalWrite(REF_GAIN_A1,LOW);
                break;

            case VoltGain2X:
                digitalWrite(REF_GAIN_A0,HIGH);
                digitalWrite(REF_GAIN_A1,LOW);
                break;

            case VoltGain5X:
                digitalWrite(REF_GAIN_A0,LOW);
                digitalWrite(REF_GAIN_A1,HIGH);
                break;

            case VoltGain10X:
                digitalWrite(REF_GAIN_A0,HIGH);
                digitalWrite(REF_GAIN_A1,HIGH);
                break;

            default:
                break;
        }
    }
#endif

#if defined HARDWARE_VERSION_0P2
    VoltGain AnalogSubsystem::getRefElectVoltGain() const
    {
        uint8_t value0 = digitalRead(REF_GAIN_A0);
        uint8_t  value1 = digitalRead(REF_GAIN_A1);
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
#endif


} // namespace ps
