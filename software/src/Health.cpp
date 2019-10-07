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


HealthData Health::read()
{
    HealthData data;

    return data;
}

HealthData Health::poll()
{
    HealthData data;

    return data;
}

void Health::enable()
{

}

void Health::disable()
{

}
