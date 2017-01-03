const int AD8520_GAIN_A0 = 0;
const int AD8520_GAIN_A1 = 1;

const int TIA_SW1_IN1 = 2;
const int TIA_SW1_IN2 = 5;
const int TIA_SW1_IN3 = 6;
const int TIA_SW1_IN4 = 7;

const int TIA_SW2_IN1 = 8;
const int TIA_SW2_IN2 = 9;
const int TIA_SW2_IN3 = 22;
const int TIA_SW2_IN4 = 23;

const int DAC_UNI_PIN = A14;
const int TIA_OUT_UNI_PIN = A1;

void setup()
{
    Serial.begin(115200); 

    pinMode(AD8520_GAIN_A0,OUTPUT);
    pinMode(AD8520_GAIN_A1,OUTPUT);

    digitalWrite(AD8520_GAIN_A0,LOW);
    digitalWrite(AD8520_GAIN_A1,LOW);

    pinMode(TIA_SW1_IN1,OUTPUT);
    pinMode(TIA_SW1_IN2,OUTPUT);
    pinMode(TIA_SW1_IN3,OUTPUT);
    pinMode(TIA_SW1_IN4,OUTPUT);

    pinMode(TIA_SW2_IN1,OUTPUT);
    pinMode(TIA_SW2_IN2,OUTPUT);
    pinMode(TIA_SW2_IN3,OUTPUT);
    pinMode(TIA_SW2_IN4,OUTPUT);

    digitalWrite(TIA_SW1_IN1,HIGH);
    digitalWrite(TIA_SW1_IN2,LOW);
    digitalWrite(TIA_SW1_IN3,HIGH);
    digitalWrite(TIA_SW1_IN4,HIGH);

    digitalWrite(TIA_SW2_IN1,HIGH);
    digitalWrite(TIA_SW2_IN2,LOW);
    digitalWrite(TIA_SW2_IN3,HIGH);
    digitalWrite(TIA_SW2_IN4,HIGH);


    analogWriteResolution(12);
    analogReadResolution(16);
    analogReadAveraging(16);
    analogReference(INTERNAL);

}

void loop()
{
    static int cnt = 0;
    static bool state = true;

    int val = int(0.9*(cnt - 2047)) + 2047;
    analogWrite(DAC_UNI_PIN,val);
    uint16_t value = analogRead(TIA_OUT_UNI_PIN);
    //cnt = (cnt+1)%4096;
    if (state)
    {
        cnt = cnt+3;
        if (cnt >= 4095)
        {
            state = false;
            cnt = 4095;
        }
    }
    else
    {
        cnt = cnt-3;
        if (cnt <= 0)
        {
            state = true;
            cnt = 0;
        }
    }
    delay(1);
}
