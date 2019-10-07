#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

#include "Sensor.hpp"

class Health : public Sensor
{
    public:

        Health();
        ~Health();
            
        bool init() override;
        Data read() override;
        Data poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __HEALTH_HPP__

