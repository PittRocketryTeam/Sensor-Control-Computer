#include "Photocell.hpp"


Photocell::Photocell() : 
    Sensor()
{

}

bool Photocell::init()
{
    return false;
}

Data Photocell::read(Data data)
{
    // TODO: Set data.photocellData.brightness

    return data;
}

Data Photocell::poll(Data data)
{
    // TODO: Set data.photocellData.brightness

    return data;
}

void Photocell::enable()
{

}

void Photocell::disable()
{

}

