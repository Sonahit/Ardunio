#include <ArduinoJson.h>
#define SERIAL_BUFFER_SIZE_RX 1024

Led led1 = Led(8 ,  0);
Led led2 = Led(9 ,  0);
Led led3 = Led(10 , 0);
Led led4 = Led(11 , 0);
Led led5 = Led(12 , 0);
Led led6 = Led(13 , 0); 
Led ledJson = Led(0,0);

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
        DynamicJsonDocument doc(2048);
        JsonArray data = doc.createNestedArray("data");
        if(Serial.available())
        {
            DynamicJsonDocument json(200);
            Serial.setTimeout(50);
            String input = Serial.readStringUntil("\n");
            DeserializationError err = deserializeJson(json, input);
            if(!err)
            {
                JsonObject obj = json.createNestedObject("obj");
                ledJson.setPin(json["pin"]);
                ledJson.setBrightness(json["brightness"]);
                analogWrite(json["pin"], json["brightness"]);
                obj["pin"] = ledJson.getPin();
                obj["brightness"] = ledJson.getBrightness();
                data.add(obj);
            }
        }
        for (int i = 0; i < length; i++)
        {
            if(leds[i].getPin() != ledJson.getPin())
            {
                DynamicJsonDocument json(200);
                JsonObject obj = json.createNestedObject("obj");
                obj["pin"] = leds[i].getPin();
                obj["brightness"] = leds[i].getBrightness();
                analogWrite(leds[i].getPin(), leds[i].getBrightness());
                data.add(obj); 
            } 
        }
        String output = doc.as<String>();
        Serial.println("{start}" + output + "{done}");
        Serial.flush();
        /*
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
                        if(activeLength >= sizeof(activeLeds) / sizeof(*activeLeds))
                        {
                            activeLength -= 1;
                        }
                    
                    }               
                    if (leds[i].getPin() == doc["pin"] && !hasPin)
                    {
                        activeLeds[activeLength] = Led(leds[i].getPin(), doc["brightness"]);
                        activeLength += 1 ;
                        
                    }
                if (hasPin)
                        {
                            activeLeds[pos].setPin(0);
                            activeLeds[pos].setBrightness(0);
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
            if(leds[i].getPin() == activeLeds[j].getPin())
            {
               bright = false;
            }
        }
        if(bright)
        {
            analogWrite(leds[i].getPin(), leds[i].getBrightness());
        }
    }*/
}