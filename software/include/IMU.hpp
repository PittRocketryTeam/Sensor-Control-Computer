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
        
        bool init();
        std::vector<float> read();
        std::vector<float> poll();
        void enable();
        void disable();
};


// __IMU_HPP_