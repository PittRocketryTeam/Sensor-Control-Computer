#include "board.hpp"
#include "Logger.hpp"
#include "Error.hpp"

Logger::Logger() :
    num_sensors(0)
{

}

Logger::~Logger() {}

bool Logger::init()
{
    // Initialize RTC
    setSyncProvider(getTeensy3Time);
    delay(100);
    RTC_set_successfully = (timeStatus() == timeSet);

    generateFilename();  // Generate unique log filename

    int i;
    for (i = 0; i < CONN_ATTEMPTS; ++i)
    {
        Error::reset(LOG_INIT);
        int status = SD.begin(BUILTIN_SDCARD);
        if (status)
        {
            break;
        }
        Error::display(LOG_INIT, WARN);
        delay(CONN_DELAY);
    }
    if (i == 10)
    {
        Error::display(LOG_INIT, FATAL);
    }

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

    current_time = now();
    if (RTC_set_successfully)
    {
        sprintf(filename, "%d-%d-%d_%d-%d-%d.csv", 
                month(current_time),
                day(current_time),
                year(current_time),
                hour(current_time),
                minute(current_time),
                second(current_time)
               );        
    }
    else
    {
        sprintf(filename, "loggylog.csv");
    }

}

Data Logger::readDataFromSensors()
{
    Data data;
    int i;
    for (i = 0; i < num_sensors; ++i)
    {
        data = sensors[i]->read(data);
    }

    // Add timestamp
    current_time = now();
    data.timestamp = (long int)current_time;  
    return data;                        
}

bool Logger::writeToMemory(Data data)
{
    if (!handle)
    {
        return false;
    }

    handle.printf("%ld, ,%f,%f,%f, ,%f,%f,%f, , %f,%f,%f, ,%f,%f\n",
            data.timestamp,

            data.altimeterData.temperature, 
            data.altimeterData.pressure, 
            data.altimeterData.altitude,
            
            // data.gpsData.time, 
            // data.gpsData.latitude, 
            // data.gpsData.lat_direction, 
            // data.gpsData.longitude, 
            // data.gpsData.long_direction, 
            // data.gpsData.fix_quality, 
            // data.gpsData.number_of_satellites, 
            // data.gpsData.hdop, 
            // data.gpsData.altitude, 
            // data.gpsData.rssi,
            
            // data.healthData.main_battery_temperature, 
            // data.healthData.main_battery_voltage, 
            // data.healthData.reg_5V_battery_temperature, 
            // data.healthData.reg_5V_battery_voltage, 
            // data.healthData.reg_3V3_battery_temperature, 
            // data.healthData.reg_3V3_battery_voltage,
            
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

time_t Logger::getTeensy3Time()
{
    return Teensy3Clock.get();
}