#include "GPS.hpp"


GPS::GPS() : 
    Sensor()
{

}

bool GPS::init()
{
    return false;
}

std::vector<float> GPS::read()
{
    std::vector<float> ret(GPS_DIMENSIONS, 0);

    return ret;
}

std::vector<float> GPS::poll()
{
    std::vector<float> ret(GPS_DIMENSIONS, 0);

    return ret;
}

void GPS::enable()
{

}

void GPS::disable()
{

}

