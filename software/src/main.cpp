#include <Arduino.h>
#include "board.hpp"
#include "Error.hpp"
#include "Data.hpp"
#include "Altimeter.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

#define MODE_IDLE 0
#define MODE_STARTUP 1
#define MODE_FLIGHT 2

GPS gps;
IMU acc;
Altimeter alt;

Logger logger;

Data state;
Timer log_flush;
Timer txrx;

static uint8_t mode = 1;
static uint8_t transition = 1;

void idle();
void idle_transition();

void startup();
void startup_transition();

void flight();
void flight_transition();

void setup()
{
    Error::init();

    Serial.begin(9600);
    int i;
    for (i = 0; i < CONN_ATTEMPTS; i++)
    {
        if (Serial)
        {
            break;
        }
        Serial.println("SER BAD");
        
        Error::on(SERIAL_INIT);
        delay(CONN_DELAY);
    }
    Error::off();
    if (i >= CONN_ATTEMPTS)
    {
        Error::display(SERIAL_INIT, FATAL);
    }

    // Initialize sensors
    gps.init();

    acc.init();

    alt.init();

    // Initialize logger and add sensors
    logger.init();
    logger.addSensor(&gps);
    logger.addSensor(&acc);
    logger.addSensor(&gps);
    logger.addSensor(&alt);

    Error::summary();

    txrx.setInterval(1000);
    log_flush.setInterval(1000);
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
        
    }
}

void idle()
{
    // do nothing
}

void idle_transition()
{
    // disable everything except GPS

    // set timers
    log_flush.setInterval(6000);
    txrx.setInterval(2000);
}

void startup()
{
    state = alt.poll(state);
    state = acc.poll(state);
    state = gps.poll(state);

    logger.writeToMemory(state);
}

void startup_transition()
{
    // enable all sensors

    // set timers
    log_flush.setInterval(5000);
    txrx.setInterval(1000);
}

void flight_transition()
{
    
}

void flight()
{
    // run apogee detect, land detect, approx landing coords
}
