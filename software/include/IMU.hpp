#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Sensor.hpp"

#define IMU_DIMENIONS 5
#define I2C_ADDR 0x28

class IMU : public Sensor
{
    private:
        Adafruit_BNO055 sensor;
        bool verbose;

    public:

        IMU();
        IMU(bool);
        ~IMU();

        bool init() override;
        std::vector<float> read() override;
        std::vector<float> poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __IMU_HPP__
