#include "Health.hpp"

Health::Health() :
    Sensor()
{

}

Health::~Health()
{

}

bool Health::init()
{
    return false;
}

std::vector<float> Health::read()
{
    return std::vector<float>();
}

std::vector<float> Health::poll()
{
    return std::vector<float>();
}

void Health::enable()
{

}

void Health::disable()
{

}
