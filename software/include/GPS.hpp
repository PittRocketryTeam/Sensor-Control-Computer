#ifndef __GPS_HPP__
#define __GPS_HPP__

#include "Sensor.hpp"

#define GPS_DIMENSIONS 5

class GPS : public Sensor
{
    public:

        GPS();
        ~GPS();
        
        bool init() override;
        std::vector<float> read() override;
        std::vector<float> poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __GPS_HPP__