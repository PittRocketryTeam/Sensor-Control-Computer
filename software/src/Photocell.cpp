#include "Photocell.hpp"


Photocell::Photocell()
{

}

bool Photocell::init()
{
    return false;
}

std::vector<float> Photocell::read()
{
    std::vector<float> ret(PHOTOCELL_DIMENSIONS, 0);

    return ret;
}

std::vector<float> Photocell::poll()
{
    std::vector<float> ret(PHOTOCELL_DIMENSIONS, 0);

    return ret;
}

void Photocell::enable()
{

}

void Photocell::disable()
{

}

