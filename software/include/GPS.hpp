#ifndef __GPS_HPP__
#define __GPS_HPP__

#include "Sensor.hpp"

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
        float time;
        float latitude;
        float lat_direction;
        float longitude;
        float long_direction; 
        float fix_quality;
        float number_of_satellites;
        float hdop;
        float altitude;
        float rssi;

};

#endif
// __GPS_HPP__