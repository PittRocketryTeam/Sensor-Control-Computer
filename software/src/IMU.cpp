#include "IMU.hpp"



IMU::IMU()
{
    sensor = Adafruit_BNO055(55, I2C_ADDR);
    verbose = false;
}

IMU::IMU(bool v)
{
    sensor = Adafruit_BNO055(55, I2C_ADDR);
    verbose = v;
}

bool IMU::init()
{

    while(!sensor.begin())
    {
        if (verbose) {
            Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        }
        delay(100);
    }

    sensor.setExtCrystalUse(true);

    if (verbose) {
        Serial.println("BNO055 Initialized successfully!");
    }

    return false;
}

std::vector<float> IMU::read()
{
    if (verbose) {
        imu::Vector<3> v = sensor.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

        Serial.println(v[0]);
        Serial.println(v[1]);
        Serial.println(v[2]);
    }

    std::vector<float> ret(IMU_DIMENIONS, 0);

    sensors_event_t event;
    sensor.getEvent(&event);

    ret[0] = event.orientation.x;
    ret[1] = event.orientation.y;
    ret[2] = event.orientation.z;

    return ret;
}

std::vector<float> IMU::poll()
{
    std::vector<float> ret(IMU_DIMENIONS, 0);

    return ret;
}

void IMU::enable()
{
    if (verbose) {
        Serial.println("IMU Enabled");
    }

    sensor.enterNormalMode();
}

void IMU::disable()
{
    if (verbose) {
        Serial.println("IMU Enabled");
    }

    sensor.enterSuspendMode();
}
