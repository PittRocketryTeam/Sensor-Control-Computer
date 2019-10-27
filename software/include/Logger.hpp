#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "assert.h"
#include "Sensor.hpp"
#include <SPI.h> 
#include "Time.h"
#include "SdFat.h"

#define BUILTIN_SDCARD 254

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
         * Returns true if data was successfully written, false if not (either because
         * the number of bytes that should have been written to the disk was not written
         * or because the micro SD couldn't be opened).
         */
        virtual bool log();

        SdFat SD;

    private:

        /**
         * Create a unique log file name based on the current time and date and
         * return it.
         * 
         * Example log filename: Monday_10-07-2019_03:26:41.log
        */
        virtual void generateFilename(char filename[]);

        virtual Data readDataFromSensors();

        virtual bool writeToMemory(Data data);

        /**
         * Sensors to log data from.
         */
        std::vector<Sensor*> sensors;

        /**
         * Logfile name.
        */
        char filename[128];
};

#endif
// __LOGGER_HPP__