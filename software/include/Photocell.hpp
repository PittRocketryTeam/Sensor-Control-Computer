#ifndef __PHOTOCELL_HPP__
#define __PHOTOCELL_HPP__

#include "Sensor.hpp"

class Photocell : public Sensor
{
    public:

        Photocell();
        ~Photocell();
        
        bool init() override;
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;
};

#endif
// __PHOTOCELL_HPP__