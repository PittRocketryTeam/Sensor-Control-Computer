#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Transceiver.hpp"

class XBee : Transceiver
{
    public:

        XBee();
        ~XBee();

        std::vector<float> read();
        bool write(const std::string buf, int len);
        std::vector<float> poll();
        void enable();
        void disable();
};

#endif
// __XBEE_HPP__