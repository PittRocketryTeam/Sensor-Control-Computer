#ifndef __GPS_HPP__
#define __GPS_HPP__

#include "Sensor.hpp"

#define GPS_DIMENSIONS 5

typedef struct GpsData
{
    int time;
    float latitude;
    char lat_direction;
    float longitude;
    char long_direction;
    int fix_quality;
    int number_of_satellites;
    float hdop;
    float altitude;
    float rssi;
} GpsData;

class GPS : public Sensor<GpsData>
{
    public:

        GPS();
        ~GPS();
        
        bool init() override;
        GpsData read() override;
        GpsData poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __GPS_HPP__