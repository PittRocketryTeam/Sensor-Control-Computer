#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "Sensor.hpp"
#include <SD.h>
#include <SPI.h> 
#include "Time.h"
#include "SdFat.h"

class Logger
{
    public:

        Logger();
        ~Logger();

        /**
         * Initialize the logger. Returns false if the initialization fails for 
         * any reason.
        */
        virtual bool init();

        /*
         * Add a sensor to the logger's list of sensors.
         */
        virtual void addSensor(Sensor* sensor);

        /**
         * Add a vector of sensors to the logger's list of sensors.
        */
       virtual void addSensors(std::vector<Sensor*> sens);

        /**
         * Reads from each sensor and writes the timestamped data to the disk. 
         * Returns true if data was successfully written, false if not (e.g. if 
         * the disk somehow ran out of space).
         */
        virtual bool log();

    private:

        /**
         * Create a unique log file name based on the current time and date and
         * return it.
         * 
         * Example log filename: Monday_10-07-2019_03:26:41.log
        */
        virtual char* generateFilename();

        /**
         * Sensors to log data from.
         */
        std::vector<Sensor*> sensors;

        /**
         * Logfile name.
        */
        const char* log_filename;
};

#endif
// __LOGGER_HPP__