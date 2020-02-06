#include "Error.hpp"
#include <Arduino.h>

int Error::b0;
int Error::b1;
int Error::b2;
int Error::leds[] = {DEBUG_LED_1, DEBUG_LED_2, DEBUG_LED_3};
int Error::clean = 1;
int Error::accumulated[8];

bool Error::init()
{

    memset(accumulated, 0, 8 * sizeof(int));

    pinMode(DEBUG_LED_1, OUTPUT);
    pinMode(DEBUG_LED_2, OUTPUT);
    pinMode(DEBUG_LED_3, OUTPUT);

    return true;
}

void Error::reset(int ec)
{
    int code = (int)ec;
    b0 = (code >> 0) & 0x1;
    b1 = (code >> 1) & 0x1;
    b2 = (code >> 2) & 0x1;
    off();
}

void Error::display(int ec, errtype_t type)
{
    clean = 0;

    if (type == FATAL)
    {
        accumulated[ec] = 1;
    }

    int code = (int)ec;
    b0 = (code >> 0) & 0x1;
    b1 = (code >> 1) & 0x1;
    b2 = (code >> 2) & 0x1;

    if (type == WARN)
    {
        on();
    }
    else if (type == FATAL)
    {
        for (int i=0; i < 2; i++)
        {
            on();
            delay(ERROR_DELAY * 2);
            off();
            delay(ERROR_DELAY * 2);
        }
    }
    
}

void Error::on(int ec)
{
    int code = (int)ec;
    b0 = (code >> 0) & 0x1;
    b1 = (code >> 1) & 0x1;
    b2 = (code >> 2) & 0x1;
    on();
}

void Error::on()
{
    analogWrite(DEBUG_LED_1, 1023 * b0);
    digitalWrite(DEBUG_LED_2, b1);
    digitalWrite(DEBUG_LED_3, b2);
}

void Error::off()
{
    analogWrite(DEBUG_LED_1, 0);
    digitalWrite(DEBUG_LED_2, LOW);
    digitalWrite(DEBUG_LED_3, LOW);
}

void Error::summary()
{
    for (int i = 0; i < 8; i++)
    {
        if (!accumulated[i])
        {
            continue;
        }
        display(i, FATAL);
        delay(ERROR_DELAY * 4);
    }
}

void Error::success()
{
    if (!clean) return;
    int last = 2;
    (void)last;
    int cur = 0;
    for (int i = 0; i < 10 * 3; i++)
    {
        cur = i % 3;

        if (last == 0)
        {
            analogWrite(leds[last], 0);
        }
        else
        {
            digitalWrite(leds[last], LOW);
        }

        if (cur == 0)
        {
            analogWrite(leds[cur], 1023);
        }
        else
        {
            digitalWrite(leds[cur], HIGH);
        }
        
        delay(ERROR_DELAY / 2);

        last = cur;
    }

    if (cur == 0)
    {
        analogWrite(leds[cur], 0);
    }
    else
    {
        digitalWrite(leds[cur], LOW);
    }
}