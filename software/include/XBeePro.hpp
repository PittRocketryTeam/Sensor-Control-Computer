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
    private:
        //Initiate objects  
        XBee xbee_pro; 
        XBeeResponse response;
        uint8_t *payload; 
        Tx64Request tx64; 
        Rx64Response rx64;
        TxStatusResponse txStatus;

};

#endif
// __XBEE_HPP__