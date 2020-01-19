#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "Sensor.hpp"
#include <Wire.h>

class Altimeter : public Sensor
{
    public:

        Altimeter();
        ~Altimeter();
        
        virtual bool init();
        Data read(Data data) override;
        Data poll(Data data) override;
        void enable() override;
        void disable() override;
        void setBaselinePressure();

    private:
        
};

#endif
// __ALTIMETER_HPP__