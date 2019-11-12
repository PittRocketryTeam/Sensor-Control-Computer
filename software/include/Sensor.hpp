#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include <vector>
#include "Wire.h"
#include "Data.hpp"

class Sensor
{
    public:

        Sensor() {}
        ~Sensor() {}

        /* 
         * Initialize the sensor so it can be used. Return true if the 
         * sensor is initialized and ready to be enabled, disabled, read, or 
         * polled, and false otherwise.
         * 
         * \return true if the sensor was successfully initialized
         */
        virtual bool init() = 0;

        /*
         * Return latest values read (last time poll was called).
         * 
         * \param Data the data struct to populate and return
         * \return populated data struct
         */
        virtual Data read(Data data) = 0;

        /*
         * Read fresh data from the sensor, store it in internal data fields, and 
         * return it.
         * 
         * \param Data the data struct to populate and return
         * \return populated data struct
         */
        virtual Data poll(Data data) = 0;

        /*
         * Enable the sensor to be read.
         */
        virtual void enable() = 0;

        /*
         * Disable the sensor from being read.
         */
        virtual void disable() = 0;
    
    protected:

        /*
         * Maintains the state of the sensor. It can only be enabled or disabled.
         * Only if the sensor is enabled can the read() and poll() functions be called.
         */
        enum sensor_state { ENABLED, DISABLED };
        sensor_state state;
};

#endif
// __SENSOR_HPP__