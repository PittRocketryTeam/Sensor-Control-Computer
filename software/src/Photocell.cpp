#include "Photocell.hpp"


Photocell::Photocell() : 
    Sensor()
{

}

bool Photocell::init()
{
    return false;
}

Data Photocell::read()
{
    Data data = { 0 };

    return data;
}

Data Photocell::poll()
{
    Data data = { 0 };

    return data;
}

void Photocell::enable()
{

}

void Photocell::disable()
{

}

