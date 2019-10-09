#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "Sensor.hpp"

#define I2C_ADDR 0x28

class IMU : public Sensor
{
    public:

        IMU();
        ~IMU();
        
        bool init() override;
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;
};

#endif
// __IMU_HPP__