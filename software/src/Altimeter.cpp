#include "Altimeter.hpp"


Altimeter::Altimeter()
{

}

bool Altimeter::init()
{
    return false;
}

std::vector<float> Altimeter::read()
{
    std::vector<float> ret(ALTIMETER_DIMENSIONS, 0);

    return ret;
}

std::vector<float> Altimeter::poll()
{
    std::vector<float> ret(ALTIMETER_DIMENSIONS, 0);

    return ret;
}

void Altimeter::enable()
{

}

void Altimeter::disable()
{

}

