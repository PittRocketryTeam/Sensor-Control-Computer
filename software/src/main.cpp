#include <Arduino.h>
#include "board.hpp"
#include "Error.hpp"
#include "Data.hpp"
#include "Altimeter.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Timer.hpp"
#include "Xbee.hpp"
#include "Health.hpp"

#define MODE_IDLE 0
#define MODE_STARTUP 1
#define MODE_FLIGHT 2

GPS gps;
IMU acc;
Altimeter alt;
XBee xbee;
Logger logger;
Health health;

Data state;

Timer log_flush;
Timer txrx;
Timer gps_poll;
IntervalTimer gps_interrupt;

static uint8_t mode = MODE_STARTUP;
static uint8_t transition = 1;

void idle();
void idle_transition();

void startup();
void startup_transition();

void flight();
void flight_transition();

void gps_read_callback()
{
    gps.internal_read();
}

void setup()
{
    // clean data
    memset(&state, 0, sizeof(Data));

    Error::init();

    Serial.begin(9600);
    int i;
    for (i = 0; i < CONN_ATTEMPTS; i++)
    {
        if (Serial)
        {
            break;
        }

        Error::on(SERIAL_INIT);
        delay(CONN_DELAY * 3);
    }
    Error::off();
    if (i >= CONN_ATTEMPTS)
    {
        Error::display(SERIAL_INIT, FATAL);
    }
    else
    {
        Serial.println("SERIAL OK");
    }

    acc.init();
    alt.init();
    health.init();

    // Initialize sensors
    gps.init();
    gps_interrupt.begin(gps_read_callback, 1000);

    // Initialize logger and add sensors
    logger.init();

    Error::summary();

    txrx.setInterval(1000);
    log_flush.setInterval(5000);
    gps_poll.setInterval(1000);
}

void loop()
{
    if (transition)
    {
        transition = 0;
        switch(mode)
        {
            case MODE_IDLE:
            idle_transition();
            break;

            case MODE_STARTUP:
            startup_transition();
            break;

            case MODE_FLIGHT:
            flight_transition();
            break;
        }
        return;
    }

    switch(mode)
    {
        case MODE_IDLE:
            idle();
            break;

            case MODE_STARTUP:
            startup();
            break;

            case MODE_FLIGHT:
            flight();
            break;
    }

    if (log_flush.check())
    {
        logger.flush();
    }

    if (txrx.check())
    {
        xbee.transmit();
        delay(100);
        xbee.receive();
    }
}

void poll()
{
    state.timestamp = millis();
    state = alt.poll(state);
    state = acc.poll(state);
    if (gps_poll.check())
    {
        state = gps.poll(state);
    }
    state = health.poll(state);

    xbee.setCachedData(state);
    logger.writeToMemory(state);
}

void idle()
{
    if (xbee.getModeFromGC() == 1)
    {
        mode = MODE_STARTUP;
        transition = 1;
    }
}

void idle_transition()
{
    // disable everything except GPS

    // set timers
    gps_poll.setInterval(1000);
    log_flush.setInterval(5000);
    txrx.setInterval(1000);
}

void startup()
{
    if (xbee.getModeFromGC() == 0)
    {
        //mode = MODE_IDLE;
        //transition = 1;
    }

    poll();
}

void startup_transition()
{
    // enable all sensors

    // set timers
    gps_poll.setInterval(1000);
    log_flush.setInterval(5000);
    txrx.setInterval(1000);
}

void flight_transition()
{
    gps_poll.setInterval(1000);
    txrx.setInterval(1000);   
}

void flight()
{
    // run apogee detect, land detect, approx landing coords
    poll();
}
