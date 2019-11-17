#include <Arduino.h>
#include "Data.hpp"
#include "Altimeter.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"

// IMU gyro(true);
// Altimeter alt;
GPS gps;
Logger logger;
// AnalogDevices ad;
//LaunchDetect launchDetect;

Data state;

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;

void ready();
void armed();

void setup()
{
    Serial.begin(9600);
    delay(1000);

    log_flush.setInterval(5000);

    // Initialize sensors and logger
    gps.init();
    logger.init();

    logger.addSensor(&gps);
}

void loop()
{
    mode = 0;
    lastmode = mode;

    if (lastmode != mode)
    {
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
        swtch = 1;
    }

    if (mode == 1)
    {
        ready();
    }
    else if (mode == 0)
    {
        armed();
    }

    if (log_flush.check())
    {
        digitalWrite(13, 1);
        logger.flush();
        digitalWrite(13, 0);
    }
}

void ready()
{
    if (swtch)
    {
        //logger.close();
        swtch = 0;
    }
}

void armed()
{
    if (swtch)
    {
        // digitalWrite(13, 1);
        // delay(100);
        // digitalWrite(13, 0);
        // delay(100);
        // digitalWrite(13, 1);
        // delay(100);
        // digitalWrite(13, 0);
        // delay(100);
        // digitalWrite(13, 1);
        // delay(100);
        // digitalWrite(13, 0);
        // delay(100);
        logger.reopen();
        swtch = 0;
    }

    state = gps.poll(state);

    Serial.printf("Logging\n");
    logger.log();

    delay(1000);
}
