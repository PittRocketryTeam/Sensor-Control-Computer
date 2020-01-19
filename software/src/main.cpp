#include <Arduino.h>
#include "board.hpp"
#include "Error.hpp"
#include "Data.hpp"
#include "Altimeter.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"

#define MODE_IDLE 0
#define MODE_STARTUP 1
#define MODE_FLIGHT 2

GPS gps;
Logger logger;
<<<<<<< HEAD
IMU accl;
Altimeter alt;

=======
>>>>>>> 2f6a9acaa0955287baf55afa4cd7b5e708fb8adf
Data state;
Metro log_flush;
Metro txrx;

static uint8_t mode = 0;
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

    accl.init();

    alt.init();

    // Initialize logger and add sensors
    logger.init();
    logger.addSensor(&gps);

    Error::summary();
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
        // transmit and recv
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
    log_flush.setInterval(60000);
    txrx.setInterval(2000);
}

void startup()
{
    // run launch detect
}

void startup_transition()
{
    // enable all sensors

    // set timers
    log_flush.setInterval(5000);
    txrx.setInterval(500);
}

void flight_transition()
{
    
}

void flight()
{
    // run apogee detect, land detect, approx landing coords
}
