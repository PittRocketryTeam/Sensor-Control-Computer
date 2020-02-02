#include "Timer.hpp"
#include <Arduino.h>

Timer::Timer() :
    interval(1000),
    catchup(false)
{
    then = millis();
    left = interval;
}

Timer::~Timer()
{

}

void Timer::setInterval(uint32_t iv)
{
    interval = iv;
    start();
    reset();
}

void Timer::setCatchup(bool val)
{
    catchup = val;
}

bool Timer::check()
{
    now = millis();
    delta = now - then;
    then = now;

    left -= delta;

    if (left <= 0)
    {
        reset();
        return true;
    }

    return false;
}

void Timer::reset()
{
    if (catchup)
    {
        left += interval;
    }
    else
    {
        left = interval;
    }
}

void Timer::start()
{
    then = millis();
}