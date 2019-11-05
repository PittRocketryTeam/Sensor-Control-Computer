#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <vector>
// #include "Sensor.hpp"

#define IMU_DIMENIONS 3
#define I2C_ADDR 0x28


class IMU //: public Sensor
{
    private:
        Adafruit_BNO055 sensor;
        bool verbose;
        std::vector<float> *poll_vector_ptr = nullptr;

    public:

        IMU();
        IMU(bool);
        ~IMU();

        bool init();
        std::vector<float> read();
        std::vector<float> read_raw(Adafruit_BNO055::adafruit_vector_type_t);
        std::vector<float> poll();

        void enable();
        void disable();
};

#endif
// __IMU_HPP__
