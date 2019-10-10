#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

#include "Sensor.hpp"

class Health : public Sensor
{
    public:

        Health();
        ~Health();
            
        bool init() override;
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;
};

#endif
// __HEALTH_HPP__

