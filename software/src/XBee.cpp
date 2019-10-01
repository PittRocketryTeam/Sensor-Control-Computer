#include "XBee.hpp"

XBee::XBee()
{

}

std::vector<float> XBee::read()
{
    std::vector<float> ret(1, 0);

    return ret;
}

bool XBee::write(const std::string buf, int len)
{
    return false;
}

std::vector<float> XBee::poll()
{
    std::vector<float> ret(1, 0);

    return ret;    
}

void XBee::enable()
{

}

void XBee::disable()
{

}
