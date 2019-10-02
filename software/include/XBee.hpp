#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Transceiver.hpp"

class XBee : Transceiver
{
    public:

        XBee();
        ~XBee();

        bool init();
        std::vector<float> receive();
        bool transmit(std::vector<float> data);
        void enable();
        void disable();
};

#endif
// __XBEE_HPP__