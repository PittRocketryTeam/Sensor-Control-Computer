#include "Logger.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{
    
}

void Logger::addSensor(Sensor* sensor)
{
    sensors.push_back(sensor);
}

bool Logger::log()
{
    return false;
}