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
        virtual ~GPS();
        
        bool init() override;
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;



    private:
        Adafruit_GPS* gps;
        int my_time;
        float my_lat;
        int my_lat_direction;
        float my_lon;
        int my_long_direction; 
        int my_fix_quality;
        int my_number_of_satellites;
        int my_hdop;
        int my_alt;
        int my_rssi;
        //bool my_inStandby; 


};

#endif
// __GPS_HPP__