#ifndef __IMU_HPP__
#define __IMU_HPP__
#endif

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


// __IMU_HPP_