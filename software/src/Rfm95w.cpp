#include "Rfm95w.hpp"

Rfm95w::Rfm95w() :
    Transceiver()
{

}

Rfm95w::~Rfm95w()
{
    
}

bool Rfm95w::init()
{
    return false;
}

std::vector<float> Rfm95w::receive()
{
    std::vector<float> ret(1, 0);

    return ret;
}

bool Rfm95w::transmit(std::vector<float> data)
{
    return false;
}

void Rfm95w::enable()
{

}

void Rfm95w::disable()
{

}
