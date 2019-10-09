#ifndef __GPS_HPP__
#define __GPS_HPP__

#include "Sensor.hpp"

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
};

#endif
// __GPS_HPP__