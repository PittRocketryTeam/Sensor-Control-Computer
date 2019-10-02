#ifndef __RFM95W_HPP__
#define __RFM95W_HPP__

#include "Transceiver.hpp"

class Rfm95w : Transceiver
{
    public:

        Rfm95w();
        ~Rfm95w();

        bool init();
        std::vector<float> receive();
        bool transmit(std::vector<float> data);
        void enable();
        void disable();
};

#endif
// __RFM95W_HPP__