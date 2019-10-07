#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "Sensor.hpp"

class Altimeter : public Sensor
{
    public:

        Altimeter();
        ~Altimeter();
        
        bool init() override;
        Data read() override;
        Data poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __ALTIMETER_HPP__