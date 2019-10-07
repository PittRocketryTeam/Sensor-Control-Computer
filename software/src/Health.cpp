#include "Health.hpp"

<<<<<<< HEAD

Health::Health()
=======
Health::Health() :
    Sensor()
{

}

Health::~Health()
>>>>>>> 4df6e6dd0825eea7cc700fb2756b8a9ea36d1c26
{

}

bool Health::init()
{
    return false;
}

<<<<<<< HEAD
HealthData Health::read()
{
    HealthData data;

    return data;
}

HealthData Health::poll()
{
    HealthData data;

    return data;
=======
std::vector<float> Health::read()
{
    return std::vector<float>();
}

std::vector<float> Health::poll()
{
    return std::vector<float>();
>>>>>>> 4df6e6dd0825eea7cc700fb2756b8a9ea36d1c26
}

void Health::enable()
{

}

void Health::disable()
{

}
<<<<<<< HEAD

=======
>>>>>>> 4df6e6dd0825eea7cc700fb2756b8a9ea36d1c26
