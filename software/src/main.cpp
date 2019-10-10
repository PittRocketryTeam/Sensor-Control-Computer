#include <Arduino.h>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Altimeter.hpp"
#include "Logger.hpp"
#include "Photocell.hpp"
#include "XBee.hpp"
#include "Rfm95w.hpp"
#include "Health.hpp"

#include <Metro.h>

Logger logger;

GPS* gps;
IMU* imu;
Altimeter* altimeter;
Photocell* photocell;
Health* health;

std::vector<Sensor*> sensors;

void setup()
{
    sensors.push_back(gps);
    sensors.push_back(imu);
    sensors.push_back(altimeter);
    sensors.push_back(photocell);
    sensors.push_back(health);

    for (Sensor* s : sensors)
    {
        logger.addSensor(s);
    }

    logger.init();
}

void loop()
{
    logger.log();
}