#include "Logger.hpp"

Logger::Logger() {}

Logger::~Logger() {}

bool Logger::init()
{
    Serial.begin(9600);                 // Start serial
    log_filename = generateFilename();  // Generate unique log filename
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
    // Read data from each sensor
    Data data;
    for (Sensor* s : sensors)
        data = s->read();                               
    
    // Add timestamp
    data.timestamp = now();                              

    // Open micro SD card
    File microSD = SD.open(log_filename, FILE_WRITE);   
    if (!microSD) 
        return false;
    
    // Perform write and close
    size_t bytes_written = microSD.write((uint8_t *)&data, sizeof(data)/sizeof(uint8_t));
    microSD.close();                                    

    // Check write
    if (bytes_written != sizeof(data))                 
        return false;
    
    return true;
}

char* Logger::generateFilename()
{
    char* filename = NULL;
    sprintf(filename, "%d_%d-%d-%d_%d:%d:%d.log", weekday(), month(), day(), year(), hour(), minute(), second());
    return filename;
}
