#include "GPS.hpp"


GPS::GPS() : 
    Sensor()
{

}

bool GPS::init()
{
    return false;
}

Data GPS::read(Data data)
{
    // TODO: Set data.gpsData.time
    // TODO: Set data.gpsData.latitude
    // TODO: Set data.gpsData.lat_direction
    // TODO: Set data.gpsData.longitude
    // TODO: Set data.gpsData.long_direction
    // TODO: Set data.gpsData.fix_quality
    // TODO: Set data.gpsData.number_of_satellites
    // TODO: Set data.gpsData.hdop
    // TODO: Set data.gpsData.altitude
    // TODO: Set data.gpsData.rssi

    return data;
}

Data GPS::poll(Data data)
{
    // TODO: Set data.gpsData.time
    // TODO: Set data.gpsData.latitude
    // TODO: Set data.gpsData.lat_direction
    // TODO: Set data.gpsData.longitude
    // TODO: Set data.gpsData.long_direction
    // TODO: Set data.gpsData.fix_quality
    // TODO: Set data.gpsData.number_of_satellites
    // TODO: Set data.gpsData.hdop
    // TODO: Set data.gpsData.altitude
    // TODO: Set data.gpsData.rssi

    return data;
}

void GPS::enable()
{

}

void GPS::disable()
{

}

