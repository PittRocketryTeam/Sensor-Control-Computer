#include "Rfm95w.hpp"

Rfm95w::Rfm95w()
{

}

std::vector<float> Rfm95w::read()
{
    std::vector<float> ret(1, 0);

    return ret;
}

bool Rfm95w::write(const std::string buf, int len)
{
    return false;
}

std::vector<float> Rfm95w::poll()
{
    std::vector<float> ret(1, 0);

    return ret;    
}

void Rfm95w::enable()
{

}

void Rfm95w::disable()
{

}
