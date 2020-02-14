#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Data.hpp"
#include <Arduino.h>

class XBee
{
    private:
        String formattedData;
        Data cachedData;
        int mode;

    public:
        XBee();
        ~XBee();
        void transmit();
        void setCachedData(Data);
        int getModeFromGC();
        Data receive();
};

#endif
