#include "GPS.hpp"


GPS::GPS() : 
    Sensor(), 
    time(0), 
    latitude(0), 
    lat_direction(0),
    longitude(0), 
    long_direction(0), 
    fix_quality(0), 
    number_of_satellites(0), 
    hdop(0), 
    altitude(0), 
    rssi(0) 
{

}

bool GPS::init()
{
    // pinMode(VBAT, INPUT); 
    pinMode(VIN_PIN, OUTPUT);
    return true;
}

Data GPS::read(Data data)
{
    data.gpsData.time = time;
    data.gpsData.latitude = latitude;
    data.gpsData.lat_direction = lat_direction;
    data.gpsData.longitude = longitude;
    data.gpsData.long_direction = long_direction;
    data.gpsData.fix_quality = fix_quality;
    data.gpsData.number_of_satellites = number_of_satellites;
    data.gpsData.hdop = hdop;
    data.gpsData.altitude = altitude;
    data.gpsData.rssi = rssi;
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
    digitalWrite(VIN_PIN, HIGH);
}

void GPS::disable()
{
    // pin is pulled to ground, it will turn off the GPS module
    // if you disable it, you will lose your fix and it will 
    // take a long time to get fix back if you dont have backup battery
    digitalWrite(VIN_PIN, LOW);   
}

