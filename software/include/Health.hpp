#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

#include "Sensor.hpp"

#define TB_PIN 0
#define VB_PIN 1
#define V5_PIN 2
#define V3_PIN 3

#define VBR1 1e6
#define VBR2 1e6
#define V5R1 1e6
#define V5R2 1e6
#define V3R1 1e6
#define V3R2 1e6

#define T0 298.15
#define ANALOG_MAX 1023


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

    private:
        float calculate_voltage(int, int, int);
        float calculate_temperature(int, float);

        float battery_temperature;
        float battery_voltage;
        float reg5_voltage;
        float reg3_voltage;
        
        bool enabled;
};

#endif /* __HEALTH_HPP__ */

