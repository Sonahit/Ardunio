#include <ArduinoJson.h>

Led led1 = Led(8 ,  0);
Led led2 = Led(9 ,  0);
Led led3 = Led(10 , 0);
Led led4 = Led(11 , 0);
Led led5 = Led(12 , 0);
Led led6 = Led(13 , 0); 

const Led leds[6]{led1, led2, led3, led4, led5, led6};
Led activeLeds[6];

const int length = sizeof(leds) / sizeof(*leds);
int activeLength = 0;
unsigned long start;
unsigned long currentTime;
const int pinTest = 7;

void setup()
{
    for (int i = 0; i < length; i++)
    {
        pinMode(leds[i].getPin(), INPUT);
    }
    pinMode(pinTest, OUTPUT);
    start = millis();
    Serial.begin(9600);
}
void loop()
{
    if(Serial.available())
    {
        DynamicJsonDocument doc(2048);
        Serial.setTimeout(50);
        String input = Serial.readStringUntil("\n");
        Serial.println(input);
        Serial.flush();
        DeserializationError err = deserializeJson(doc, input);
        if(!err)
        {
            for (int i = 0; i < length; i++)
            {
                bool hasPin = false;
                int pos = -1;
                for (int j = 0; j < activeLength; j++)
                {
                    hasPin = (leds[i].getPin() == activeLeds[j].getPin() ? true : false);
                    pos = j;
                    break;
                }               
                if (leds[i].getPin() == doc["pin"] && !hasPin)
                {
                    activeLeds[activeLength] = Led(leds[i].getPin(), doc["brightness"]);
                    activeLength += 1 ;
                    if(activeLength >= sizeof(activeLeds) / sizeof(*activeLeds))
                    {
                        activeLength -= 1;
                    }
                }
                if(hasPin)
                {
                    activeLeds[pos] = Led(0,0);
                }
            }
        }
    }
    for (int i = 0; i < activeLength; i++)
    {
        analogWrite(activeLeds[i].getPin(), activeLeds[i].getBrightness());
        delay(100);
        analogWrite(activeLeds[i].getPin(), 255);
        delay(100);
    }
    for (int i = 0; i < length; i++)
    {
        bool bright = true;
        for (int j = 0; j < activeLength; j++)
        {
            if(leds[i].getPin() != activeLeds[j].getPin())
            {
               bright = false;
               break;
            }
        }
        if(bright)
        {
            analogWrite(leds[i].getPin(), leds[i].getBrightness());
        }
    }
}