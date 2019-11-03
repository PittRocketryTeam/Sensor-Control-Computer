#ifndef __TRANSCEIVER_HPP__
#define __TRANSCEIVER_HPP__


#include <vector>
#include <string>
#include "Data.hpp"


class Transceiver
{
    public:

        Transceiver() {}
        ~Transceiver() {}

        /*
         * Initialize the trasceiver. After this function has been called,
         * the trasceiver should be configured and ready for use.
         * 
         * \return true if transceiver was successfully initialized
         */
        virtual bool init() = 0;
        
        /*
         * Receive data from another transceiver.
         * 
         * \return a vector of the data received
         */
        virtual std::vector<float> receive() = 0;
        
        /*
         * Transmit data to another transceiver.
         * 
         * \param data the data struct to transmit
         * \return true if data was successfully transmitted, false otherwise
         */
        virtual bool transmit(Data data) = 0;

        /*
         * Enable the transceiver to transmit and receive.
         */
        virtual void enable() = 0;

        /*
         * Disable the transmitter (to prevent it from being able to transmit and receive).
         */
        virtual void disable() = 0; 

    protected:

        /*
         * Maintains the state of the transceiver. It can only be enabled or disabled.
         * Only if the transceiver is enabled can the read() and poll() functions be called.
         */
        enum transceiver_state { ENABLED, DISABLED };
        transceiver_state state;
};

#endif
// __TRANSCEIVER_HPP__