#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

#include "Sensor.hpp"

typedef struct HealthData
{
    // tbd
} HealthData;

class Health : public Sensor<HealthData>
{
    public:

        Health();
        ~Health();
            
        bool init() override;
        HealthData read() override;
        HealthData poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __HEALTH_HPP__