#include <ArduinoJson.h>


Led led1 = Led(8 ,  250);
Led led2 = Led(9 ,  200);
Led led3 = Led(10 , 150);
Led led4 = Led(11 , 100);
Led led5 = Led(12 , 50);
Led led6 = Led(13 , 0); 

const Led leds[6]{led1, led2, led3, led4, led5, led6};
const int length = sizeof(leds) / sizeof(*leds);
const int capacity = JSON_OBJECT_SIZE(2);
StaticJsonDocument<capacity> doc;


const int buttonPin = 7;

void setup()
{
    for (int i = 0; i < length; i++)
    {
        pinMode(leds[i].getPin(), INPUT);
    }
    pinMode(buttonPin, INPUT);
    Serial.begin(115200);
}

void loop()
{
    for(int i = 0; i < length; i++)
    {
        leds[i].setBrightness(leds[i].getBrightness() + leds[i].getFade());
        analogWrite(leds[i].getPin(), leds[i].getBrightness());
        if(leds[i].getBrightness() <= 0 || leds[i].getBrightness() >= 255 ) 
        {
            leds[i].setFade(-leds[i].getFade());
            delay(150);
        }
    }
    for(int i = 0; i < length; i++)
    {
        JsonObject object = doc.to<JsonObject>();
        object["pin"] = leds[i].getPin();
        object["brightness"] = leds[i].getBrightness();
        delay(20);
        serializeJson(object, Serial);
    }
    
    delay(10);
}
