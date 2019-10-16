#include "Error.hpp"
#include <Arduino.h>

Error::Error() :
    b0(0),
    b1(0),
    b2(0)
{

}

Error::~Error()
{

}

bool Error::init()
{
    pinMode(DEBUG_LED_1, OUTPUT);
    pinMode(DEBUG_LED_2, OUTPUT);
    pinMode(DEBUG_LED_3, OUTPUT);

    return true;
}

void Error::display(errcode_t ec, errtype_t type)
{
    int code = (int)ec;
    b0 = (code >> 0) & 0x1;
    b1 = (code >> 1) & 0x1;
    b2 = (code >> 2) & 0x1;

    if (type == WARN)
    {
        on();
        delay(250);
        off();
    }
    else if (type == FATAL)
    {
        on();
        delay(500);
        off();
        delay(500);
        on();
        delay(500);
        off();
        delay(500);
    }
    
}

void Error::on()
{
    digitalWrite(DEBUG_LED_1, b0);
    digitalWrite(DEBUG_LED_2, b1);
    digitalWrite(DEBUG_LED_3, b2);
}

void Error::off()
{
    digitalWrite(DEBUG_LED_1, LOW);
    digitalWrite(DEBUG_LED_2, LOW);
    digitalWrite(DEBUG_LED_3, LOW);
}