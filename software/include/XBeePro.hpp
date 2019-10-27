#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Transceiver.hpp"
#include <XBee.h>

class XBeePro : Transceiver
{
    public:

        XBeePro();
        ~XBeePro();

        bool init();
        std::vector<float> receive();
        bool transmit(Data data);
        void enable();
        void disable();
};

#endif
// __XBEE_HPP__