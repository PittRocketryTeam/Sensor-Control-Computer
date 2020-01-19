#include <Arduino.h>
#include "board.hpp"
#include "Error.hpp"
#include "Data.hpp"
#include "Altimeter.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"

GPS gps;
Logger logger;
IMU accl;
Altimeter alt;

Data state;

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;

void ready();
void armed();

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

    log_flush.setInterval(5000);

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
    gps.poll(state);
}
