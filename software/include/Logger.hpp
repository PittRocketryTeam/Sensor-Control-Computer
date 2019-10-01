#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#endif

#include "Sensor.hpp"

class Logger
{
    public:

        Logger();
        ~Logger();

        /*
         * Add a sensor to the logger's list of sensors.
         */
        virtual void addSensor(Sensor sensor) = 0;
        
        /*
         * Reads from each sensor and writes the timestamped data to the disk. 
         * Returns true if data was successfully written, false if not (e.g. if 
         * the disk somehow ran out of space).
         */
        virtual bool log() = 0;

    private:

        /*
         * Sensors to log data from.
         */
        std::vector<Sensor> sensors;
};

// __LOGGER_HPP__