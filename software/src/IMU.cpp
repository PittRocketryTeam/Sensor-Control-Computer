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
    std::vector<float> ret(IMU_DIMENIONS, 0);

    sensors_event_t event;
    sensor.getEvent(&event);

    ret[0] = event.orientation.x;
    ret[1] = event.orientation.y;
    ret[2] = event.orientation.z;

    return ret;
}

std::vector<float> IMU::read_raw(Adafruit_BNO055::adafruit_vector_type_t t)
{
    std::vector<float> ret(IMU_DIMENIONS, 0);

    imu::Vector<3> v = sensor.getVector(t);

    ret[0] = v[0];
    ret[1] = v[1];
    ret[2] = v[2];

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
