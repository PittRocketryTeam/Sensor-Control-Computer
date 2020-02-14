#ifndef __XBEE_HPP__
#define __XBEE_HPP__

#include "Data.hpp"
#include <Arduino.h>
#include <cstring>
#include "constants.hpp"


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
        void receive();
};

#endif // __XBEE_HPP__
