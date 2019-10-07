#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "Sensor.hpp"

typedef struct AltimeterData
{
    float temperature;
    float pressure;
    float altitude;
} AltimeterData;

class Altimeter : public Sensor<AltimeterData>
{
    public:

        Altimeter();
        ~Altimeter();
        
        bool init() override;
        AltimeterData read() override;
        AltimeterData poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __ALTIMETER_HPP__