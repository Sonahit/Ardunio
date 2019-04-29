#include <ArduinoJson.h>

Led led1 = Led(8 ,  250);
Led led2 = Led(9 ,  200);
Led led3 = Led(10 , 150);
Led led4 = Led(11 , 100);
Led led5 = Led(12 , 50);
Led led6 = Led(13 , 0); 

const Led leds[6]{led1, led2, led3, led4, led5, led6};
const int length = sizeof(leds) / sizeof(*leds);
unsigned long start;
const int capacity = JSON_OBJECT_SIZE(2);
StaticJsonDocument<capacity> doc;
unsigned long currentTime;

const int buttonPin = 7;

void setup()
{
    for (int i = 0; i < length; i++)
    {
        pinMode(leds[i].getPin(), INPUT);
    }
    pinMode(buttonPin, INPUT);
    start = millis();
    Serial.begin(115200);
}

void loop()
{
    currentTime = millis();
    if (currentTime - start <= 10 * 1000)
    {
        for(int i = 0; i < length; i++)
        {
            leds[i].setBrightness(leds[i].getBrightness() + leds[i].getFade());
            analogWrite(leds[i].getPin(), leds[i].getBrightness());
            if(leds[i].getBrightness() <= 0 || leds[i].getBrightness() >= 255 ) 
            {
                leds[i].setFade(-leds[i].getFade());
            }
            JsonObject object = doc.to<JsonObject>();
            object["pin"] = leds[i].getPin();
            object["brightness"] = leds[i].getBrightness();
            delay(5);
            serializeJson(object, Serial);
        }
    } else {
        for(int i = 0; i < length; i++)
        {
            int pin = (int) random(0, 6);
            leds[pin].setBrightness(5);
            analogWrite(leds[pin].getPin(), leds[pin].getBrightness());

            JsonObject object = doc.to<JsonObject>();
            object["pin"] = leds[i].getPin();
            object["brightness"] = leds[i].getBrightness();

            delay(100);
            serializeJson(object, Serial);
            delay(20);
            leds[pin].setBrightness(200);
            analogWrite(leds[pin].getPin(), leds[pin].getBrightness());

            object["pin"] = leds[i].getPin();
            object["brightness"] = leds[i].getBrightness();

            delay(100);
           serializeJson(object, Serial);
        }
        start = currentTime;
    }
    delay(10);
}
