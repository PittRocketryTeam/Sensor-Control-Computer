#include "Altimeter.hpp"


Altimeter::Altimeter() :
    Sensor()
{

}

bool Altimeter::init()
{
    return false;
}

Data Altimeter::read(Data data)
{
    // TODO: Set data.altimeterData.temperature
    // TODO: Set data.altimeterData.pressure
    // TODO: Set data.altimeterData.altitude

    return data;
}

Data Altimeter::poll(Data data)
{
    // TODO: Set data.altimeterData.temperature
    // TODO: Set data.altimeterData.pressure
    // TODO: Set data.altimeterData.altitude

    return data;
}

void Altimeter::enable()
{

}

void Altimeter::disable()
{

}

