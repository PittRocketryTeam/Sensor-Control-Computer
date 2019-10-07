#ifndef __PHOTOCELL_HPP__
#define __PHOTOCELL_HPP__

#include "Sensor.hpp"

class Photocell : public Sensor
{
    public:

        Photocell();
        ~Photocell();
        
        bool init() override;
        Data read() override;
        Data poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __PHOTOCELL_HPP__