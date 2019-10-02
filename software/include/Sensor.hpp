#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include <vector>
#include "Wire.h"

class Sensor
{
    public:

        Sensor() {}
        ~Sensor() {}

        /* 
         * Initialize the sensor so it can be used. Return true if the 
         * sensor is initialized and ready to be enabled, disabled, read, or 
         * polled, and false otherwise.
         */
        virtual bool init() = 0;

        /*
         * Read current sensor data and return it as vector of floats. 
         */
        virtual std::vector<float> read() = 0;

        /*
         * TODO: Add description
         */
        virtual std::vector<float> poll() = 0;

        /*
         * TODO: Add description
         */
        virtual void enable() = 0;

        /*
         * TODO: Add description
         */
        virtual void disable() = 0;
    
    protected:

        /*
         * Maintains the state of the sensor. It can only be enabled or disabled.
         * Only if the sensor is enabled ca the read() and poll() functions be called.
         */
        enum sensor_state { ENABLED, DISABLED };
        sensor_state state;
};

#endif
// __SENSOR_HPP__