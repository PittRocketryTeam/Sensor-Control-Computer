#include "XBee.hpp"

XBee::XBee() : 
    Transceiver()
{

}

bool XBee::init()
{
    return false;
}

std::vector<float> XBee::receive()
{
    std::vector<float> ret(1, 0);

    return ret;
}

bool XBee::transmit(Data data)
{
    return false;
}

void XBee::enable()
{

}

void XBee::disable()
{

}
