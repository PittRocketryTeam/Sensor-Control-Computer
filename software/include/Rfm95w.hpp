#ifndef __RFM95W_HPP__
#define __RFM95W_HPP__

#include "Transceiver.hpp"

class Rfm95w : Transceiver
{
    public:

        Rfm95w();
        ~Rfm95w();

        std::vector<float> read();
        bool write(const std::string buf, int len);
        std::vector<float> poll();
        void enable();
        void disable();
};

#endif
// __RFM95W_HPP__