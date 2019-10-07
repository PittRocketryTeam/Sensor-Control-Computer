#include "Altimeter.hpp"


Altimeter::Altimeter() :
    Sensor()
{

}

bool Altimeter::init()
{
    return false;
}

AltimeterData Altimeter::read()
{
    AltimeterData data = { 0 };

    return data;
}

AltimeterData Altimeter::poll()
{
    AltimeterData data = { 0 };

    return data;
}

void Altimeter::enable()
{

}

void Altimeter::disable()
{

}

