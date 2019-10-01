#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "Sensor.hpp"

#define IMU_DIMENIONS 5

class IMU : public Sensor
{
    public:

        IMU();
        ~IMU();
        
        bool init() override;
        std::vector<float> read() override;
        std::vector<float> poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __IMU_HPP__