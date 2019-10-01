#ifndef __PHOTOCELL_HPP__
#define __PHOTOCELL_HPP__

#include "Sensor.hpp"

#define PHOTOCELL_DIMENSIONS 5

class Photocell : public Sensor
{
    public:

        Photocell();
        ~Photocell();
        
        bool init() override;
        std::vector<float> read() override;
        std::vector<float> poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __PHOTOCELL_HPP__