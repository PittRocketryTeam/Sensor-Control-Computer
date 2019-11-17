#include <Arduino.h>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Altimeter.hpp"
#include "Logger.hpp"
#include "Photocell.hpp"
#include "XBeePro.hpp"
#include "Rfm95w.hpp"
#include "Health.hpp"
#include <Metro.h>

Logger logger;
XBeePro XBP; 
GPS* gps;
IMU* imu0;
Altimeter* altimeter;
Photocell* photocell;
Health* health;

std::vector<Sensor*> sensors;
void setup()
{    
    Serial.begin(9600);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB.
    }
    
    //if(XBP.init())
     //   Serial.println("Xbee Pro successfully initiated.");  

   // XBP.enable(); 
   Serial1.begin(9600);
    sensors.push_back(gps);
    // sensors.push_back(imu0);
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
    // logger.log();
    //XBP.receive();  
    Serial1.println("hi"); 
    Serial1.flush();
    delay(500);
}
