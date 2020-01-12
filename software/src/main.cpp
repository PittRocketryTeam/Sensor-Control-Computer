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

Data state;

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;

void ready();
void armed();

void setup()
{
    digitalWrite(13, HIGH);
    Serial.begin(9600);
    while (!Serial)
    {
        
    }
    digitalWrite(13, LOW);
    int i;
    for (i = 0; i < CONN_ATTEMPTS; i++)
    {
        Error::display(SERIAL_INIT, WARN);
        delay(CONN_DELAY);
    }
    if (i == CONN_ATTEMPTS)
    {
        Error::display(SERIAL_INIT, FATAL);
    }

    log_flush.setInterval(5000);

    // Initialize sensors
    gps.init();

    // Initialize logger and add sensors
    logger.init();
    logger.addSensor(&gps);
}

void loop()
{
    gps.poll(state);
}
