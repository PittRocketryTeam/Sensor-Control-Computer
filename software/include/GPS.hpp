// __GPS_HPP__

#ifndef __GPS_HPP__
#define __GPS_HPP__

#include <Wire.h>
#include <Adafruit_GPS.h>
#include "Sensor.hpp"
#define GPSSerial Serial1


#define VIN_PIN 0

class GPS : public Sensor
{
    public:

        GPS();
        ~GPS();
        
        bool init() override;
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;



    private:
        Adafruit_GPS gps;
        int time;
        float lat;
        int lat_direction;
        float lon;
        int long_direction; 
        int fix_quality;
        int number_of_satellites;
        int hdop;
        int alt;
        int rssi;
        // bool inStandby; 


};

#endif
// __GPS_HPP__