#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Data.hpp"
#include "Sensor.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "Error.hpp"


class IMU : public Sensor
{
    private:
        Adafruit_BNO055 sensor;
        sensors_event_t event;

        Data last_data;

        float ax, ay, az;
        float ox, oy, oz;
        imu::Vector<3> o;
        imu::Vector<3> a;

    public:

        IMU();
        ~IMU();

        bool init();
        Data poll(Data) override;
        Data read(Data) override;

        void enable() override;
        void disable() override;
};

#endif
// __IMU_HPP__