#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "Sensor.hpp"

#define ALTIMETER_DIMENSIONS 5

class Altimeter : public Sensor
{
    public:

        Altimeter();
        ~Altimeter();
        
        bool init() override;
        std::vector<float> read() override;
        std::vector<float> poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __ALTIMETER_HPP__