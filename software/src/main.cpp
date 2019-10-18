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
#define TLED 13

Logger logger;

GPS gps;
IMU imu;
Altimeter altimeter;
Photocell photocell;
Health health;

std::vector<Sensor*> sensors;

void setup()
{    
    Serial.begin(9600);

    for(int x = 0; x < 10; x++)
    {
        if(Serial)
            break;
        delay(1000);
    }

    pinMode(TLED, OUTPUT);
    digitalWrite(TLED, HIGH);
    
    sensors.push_back(&gps);
    sensors.push_back(&imu);
    sensors.push_back(&altimeter);
    sensors.push_back(&photocell);
    sensors.push_back(&health);
    
    for (Sensor* s : sensors)
    {
        logger.addSensor(s);
    }

    logger.init();
    altimeter.init();
    
}

void loop()
{
    digitalWrite(TLED, HIGH);
    delay(1000);
    digitalWrite(TLED, LOW);
    delay(1000);

    //Serial.println("Printing");
    //logger.log();

    altimeter.setBaselinePressure();
    Data dat;
    altimeter.poll(dat);

    delay(1000);
}