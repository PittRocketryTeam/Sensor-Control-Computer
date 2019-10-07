#include "Altimeter.hpp"


Altimeter::Altimeter() :
    Sensor()
{

}

bool Altimeter::init()
{
    return false;
}

Data Altimeter::read()
{
    Data data = { 0 };

    return data;
}

Data Altimeter::poll()
{
    Data data = { 0 };

    return data;
}

void Altimeter::enable()
{

}

void Altimeter::disable()
{

}

