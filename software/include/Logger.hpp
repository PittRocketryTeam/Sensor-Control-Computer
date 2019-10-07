#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "Sensor.hpp"

template<class Data>
class Logger
{
    public:

        Logger()
        {

        }
        ~Logger()
        {

        }

        /*
         * Add a sensor to the logger's list of sensors.
         */
        virtual void addSensor(Sensor<Data>* sensor)
        {
            sensors.push_back(sensor);
        }

        /*
         * Reads from each sensor and writes the timestamped data to the disk. 
         * Returns true if data was successfully written, false if not (e.g. if 
         * the disk somehow ran out of space).
         */
        virtual bool log()
        {
            return false;
        }

    private:

        /*
         * Sensors to log data from.
         */
        std::vector<Sensor<Data>*> sensors;
};

#endif
// __LOGGER_HPP__