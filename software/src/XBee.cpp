#include "XBee.hpp"

XBee::XBee() 
{
    Serial4.begin(9600); // Serial4 is used for the PCB
}

XBee::~XBee() {}

void XBee::transmit()
{
    Serial4.println(formattedData);
    Serial4.flush();

    if (VERBOSE) { Serial.printf("XBee::transmit() - transmitted %s\n", formattedData); }
}

void XBee::setCachedData(Data newData)
{
    formattedData = "";

    formattedData += String(newData.timestamp) + ",";

    //IMU data
    formattedData += String(newData.imuData.euler_abs_orientation_x) + ",";
    formattedData += String(newData.imuData.euler_abs_orientation_y) + ",";
    formattedData += String(newData.imuData.euler_abs_orientation_z) + ",";
    formattedData += String(newData.imuData.acceleration_x) + ",";
    formattedData += String(newData.imuData.acceleration_y) + ",";
    formattedData += String(newData.imuData.acceleration_z) + ",";

    //GPS data
    formattedData += String(newData.gpsData.latitude) + ",";
    formattedData += String(newData.gpsData.longitude) + ",";
    //Altimeter data
    formattedData += String(newData.altimeterData.temperature) + ",";
    formattedData += String(newData.altimeterData.pressure) + ",";
    formattedData += String(newData.altimeterData.altitude) + ",";

    // Health data
    formattedData += String(newData.healthData.main_battery_voltage) + ",";
    formattedData += String(newData.healthData.reg_3V3_battery_voltage) + ",";
    formattedData += String(newData.healthData.reg_5V_battery_voltage) + ",";

    formattedData += "\0";
}

void XBee::receive()
{
    if (Serial4.available())
    {
        mode = Serial4.read() == 'a';
        Serial.println(mode);
        digitalWrite(13, mode);
        delay(500);
    }

    digitalWrite(13, 0);
}
