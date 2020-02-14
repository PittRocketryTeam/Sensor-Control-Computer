#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

#include "Sensor.hpp"
#include "board.hpp"
#include "constants.hpp"


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
        float calculate_voltage(int, float, float);
        float calculate_temperature(int, float);

        float battery_temperature;
        float battery_voltage;
        float reg5_voltage;
        float reg3_voltage;
        
        bool enabled;
};

#endif /* __HEALTH_HPP__ */

