#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Metro.h"

Metro::Metro() : 
    interval(1000),
    resolution(MILLIS)
{	
}

Metro::Metro(unsigned long d) : 
    interval(d),
    resolution(MILLIS)
{
}

unsigned long Metro::getTicks()
{
    if (resolution == MILLIS)
    {
        return millis();
    }
    else if (resolution == MICROS)
    {
        return micros();
    }

    return 0;
}

void Metro::setInterval(unsigned long d)
{
    interval = d;
}

void Metro::setResolution(res_t r)
{
    resolution = r;
}

uint8_t Metro::check()
{
    return check(interval);
}

uint8_t Metro::check(unsigned long d)
{
    unsigned long now = millis();
    if (d == 0)
    {
        previous = now;
        return 1;
    }

    if (now < previous)
    {
        // overflow detected
        // reset the timer and leave
        
        reset();
        return 0;
    }
    
    unsigned long delta = (now - previous) - d;

    if (delta >= 0)
    {
#ifdef NO_CATCHUP
        previous = now;
#else
        previous += d;
#endif /* NO_CATCHUP */
        return 1;
    }

    return 0;
}

void Metro::reset() 
{
    previous = millis();
}

