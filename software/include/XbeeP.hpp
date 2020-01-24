#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Data.hpp"
#include <Arduino.h>

class XBeeP
{
    private:
        String formattedData;
        Data cachedData;

    public:
        XBeeP();
        ~XBeeP();
        void transmit();
        void setCachedData(Data);
        Data receive();
};

#endif
