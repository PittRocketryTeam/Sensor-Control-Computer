#include "XBee.hpp"
#include "string.h"

XBee::XBee() {
    Serial4.begin(9600); //Serial4 is used for the PCB
}

XBee::~XBee() {}

void XBee::transmit()
{
    Serial4.println(formattedData);
    Serial4.flush();
}

void XBee::setCachedData(Data newData)
{
    formattedData = "";

    //IMU data
    formattedData += String(newData.imuData.euler_abs_orientation_x) + "\n";
    formattedData += String(newData.imuData.euler_abs_orientation_y) + "\n";
    formattedData += String(newData.imuData.euler_abs_orientation_z) + "\n";
    formattedData += String(newData.imuData.acceleration_x) + "\n";
    formattedData += String(newData.imuData.acceleration_y) + "\n";
    formattedData += String(newData.imuData.acceleration_z) + "\n";

    //GPS data
    formattedData += String(newData.gpsData.time) + "\n";
    formattedData += String(newData.gpsData.latitude) + "\n";
    formattedData += String(newData.gpsData.lat_direction) + "\n";
    formattedData += String(newData.gpsData.longitude) + "\n";
    formattedData += String(newData.gpsData.long_direction) + "\n";
    formattedData += String(newData.gpsData.fix_quality) + "\n";
    formattedData += String(newData.gpsData.number_of_satellites) + "\n";
    formattedData += String(newData.gpsData.hdop) + "\n";
    formattedData += String(newData.gpsData.altitude) + "\n";
    formattedData += String(newData.gpsData.rssi) + "\n";

    //Altimeter data
    formattedData += String(newData.altimeterData.temperature) + "\n";
    formattedData += String(newData.altimeterData.pressure) + "\n";
    formattedData += String(newData.altimeterData.altitude) + "\n";

    //Health data
    formattedData += String(newData.healthData.main_battery_temperature) + "\n";
    formattedData += String(newData.healthData.main_battery_voltage) + "\n";
    formattedData += String(newData.healthData.reg_5V_battery_temperature) + "\n";
    formattedData += String(newData.healthData.reg_5V_battery_voltage) + "\n";
    formattedData += String(newData.healthData.reg_3V3_battery_temperature) + "\n";
    formattedData += String(newData.healthData.reg_3V3_battery_voltage) + "\n";

    //Photocell data
    formattedData += String(newData.photocellData.brightness) + "\n";
}

Data XBee::receive() {
    Data newData;
    //Ground control code will receive data i think 
    return newData;
}
