#ifndef __PHOTOCELL_HPP__
#define __PHOTOCELL_HPP__

#include "Sensor.hpp"

typedef struct PhotocellData
{
    float brightness;
} PhotocellData;

class Photocell : public Sensor<PhotocellData>
{
    public:

        Photocell();
        ~Photocell();
        
        bool init() override;
        PhotocellData read() override;
        PhotocellData poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __PHOTOCELL_HPP__