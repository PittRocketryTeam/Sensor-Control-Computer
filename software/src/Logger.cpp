#include "Logger.hpp"

Logger::Logger() :
    num_sensors(0)
{

}

Logger::~Logger() {}

bool Logger::init()
{
    generateFilename();  // Generate unique log filename
    Serial.printf("filename = %s", filename);
    int i;
    for (i = 0; i < 1000; ++i)
    {
        int status = SD.begin(BUILTIN_SDCARD);
        if (status)
        {
            break;
        }
        Serial.println("cannot init sd");
    }
    delay(1000); // replace with loop
    handle = SD.open(filename, FILE_WRITE);

    return true;
}

void Logger::addSensor(Sensor* sensor)
{
    sensors[num_sensors++] = sensor;
}

bool Logger::log()
{
    Data data = readDataFromSensors();  // Read data from sensors              
    return writeToMemory(data);         // Write data to micro SD
}

void Logger::generateFilename()
{
    memset(filename, 0, sizeof(filename));
    //sprintf(filename, "%d_%d-%d-%d_%d-%d-%d.log", weekday(), month(), day(), year(), hour(), minute(), second());
    sprintf(filename, "loggylog.csv");

}

Data Logger::readDataFromSensors()
{
    Data data;
    int i;
    for (i = 0; i < num_sensors; ++i)
    {
        data = sensors[i]->read(data);
    }

    data.timestamp = millis();     // Add timestamp
    return data;                        
}

bool Logger::writeToMemory(Data data)
{
    if (!handle)
    {
        return false;
    }

    // TODO write csv format

    handle.printf("%ld, ,%f,%f,%f, ,%f,%f,%f, , %f,%f,%f, ,%f,%f\n",
            data.timestamp,

            data.altimeterData.temperature, 
            data.altimeterData.pressure, 
            data.altimeterData.altitude,
            
            /*
            data.gpsData.time, 
            data.gpsData.latitude, 
            data.gpsData.lat_direction, 
            data.gpsData.longitude, 
            data.gpsData.long_direction, 
            data.gpsData.fix_quality, 
            data.gpsData.number_of_satellites, 
            data.gpsData.hdop, 
            data.gpsData.altitude, 
            data.gpsData.rssi,
            
            data.healthData.main_battery_temperature, 
            data.healthData.main_battery_voltage, 
            data.healthData.reg_5V_battery_temperature, 
            data.healthData.reg_5V_battery_voltage, 
            data.healthData.reg_3V3_battery_temperature, 
            data.healthData.reg_3V3_battery_voltage,
            */
            
            data.imuData.euler_abs_orientation_x, 
            data.imuData.euler_abs_orientation_y, 
            data.imuData.euler_abs_orientation_z,

            data.imuData.acceleration_x,
            data.imuData.acceleration_y,
            data.imuData.acceleration_z,

            data.healthData.main_battery_temperature,
            data.photocellData.brightness
            
           // data.photocellData.brightness
    );

    return true; 
}

void Logger::flush()
{
    if (!handle)
    {
        return;
    }
    handle.flush();
}

void Logger::reopen()
{
    if (!handle)
    {
        handle = SD.open(filename, FILE_WRITE);
    }
}

void Logger::close()
{
    if (handle.isOpen())
    {
        handle.flush();
        handle.close();
    }
}