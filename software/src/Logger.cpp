#include "Logger.hpp"

Logger::Logger() {}

Logger::~Logger() {}

bool Logger::init()
{
    log_filename = generateFilename();  // Generate unique log filename
    Serial.printf("log_filename = %s", log_filename);
    return SD.begin(BUILTIN_SDCARD);    // Make sure SD card begins
}

void Logger::addSensor(Sensor* sensor)
{
    sensors.push_back(sensor);
}

void Logger::addSensors(std::vector<Sensor*> sens)
{
    
}

bool Logger::log()
{
    Serial.printf("Logging data");
    Data data = readDataFromSensors();  // Read data from sensors              
    return writeToMemory(data);         // Write data to micro SD
}

char* Logger::generateFilename()
{
    char* filename = NULL;
    sprintf(filename, "%d_%d-%d-%d_%d-%d-%d.log", weekday(), month(), day(), year(), hour(), minute(), second());
    return filename;
}

Data Logger::readDataFromSensors()
{
    Data data;
    for (Sensor* s : sensors)
        data = s->read(data);   // Read data from sensors

    data.timestamp = now();     // Add timestamp

    return data;                        
}

bool Logger::writeToMemory(Data data)
{
    File microSD = SD.open(log_filename, FILE_WRITE);  // Open micro SD card 

    if (!microSD) 
    {
        return false;
    }
        
    size_t bytes_written = microSD.write((uint8_t *)&data, sizeof(data));   // Write   
    microSD.close();                                                        // Close 
        
    return (bytes_written == sizeof(data));           // Check write
}