#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "Sensor.hpp"

class Health : public Sensor
{
public:
    Health();
    ~Health();

    bool init();
    std::vector<float> read();
    std::vector<float> poll();
    void enable();
    void disable();
};

#endif /* __IMU_HPP__ */
