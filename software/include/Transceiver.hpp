#ifndef __TRANSCEIVER_HPP__
#define __TRANSCEIVER_HPP__
#endif

#include <vector>
#include <string>

class Transceiver
{
    public:

        Transceiver();
        ~Transceiver();

        /*
         * Initialize the trasceiver. After this function has been called,
         * the trasceiver should be configured and ready for use.
         */
        virtual bool init() = 0;
        
        /*
         * TODO: Add description
         */
        virtual std::vector<float> read() = 0;
        
        /*
         * TODO: Add description
         */
        virtual bool write(const std::string buf, int len) = 0;
        
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
        enum transceiver_state { ENABLED, DISABLED };
        transceiver_state state;
};

// __TRANSCEIVER_HPP__