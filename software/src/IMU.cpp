#include "IMU.hpp"


IMU::IMU()
{

}

bool IMU::init()
{
    return false;
}

std::vector<float> IMU::read()
{
    std::vector<float> ret(IMU_DIMENIONS, 0);

    return ret;
}

std::vector<float> IMU::poll()
{
    std::vector<float> ret(IMU_DIMENIONS, 0);

    return ret;
}

void IMU::enable()
{

}

void IMU::disable()
{

}

