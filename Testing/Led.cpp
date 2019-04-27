#include  "Led.h"

Led::Led(int pin, int brightness)
{
    this -> pin = pin;
    this -> brightness = brightness;
    this -> fade = 5;
}

Led::~Led(){}

void Led::setBrightness(int brightness)
{
    this -> brightness = brightness;
}

int Led::getBrightness() const
{
    return this -> brightness;
}

int Led::getFade() const
{
    return this -> fade;
}

int Led::setFade(int fade)
{
    this -> fade = fade;
}

void Led::setPin(int pin)
{
    this -> pin = pin;
}

int Led::getPin() const
{
    return this -> pin;
}