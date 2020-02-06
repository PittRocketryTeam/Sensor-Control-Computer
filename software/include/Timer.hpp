#ifndef TIMER_HPP
#define TIMER_HPP

#include <cstdint>

class Timer
{
public:
    Timer();
    ~Timer();

    void setInterval(uint32_t);
    void setCatchup(bool);
    bool check();
    void reset();
    void start();

private:
    uint32_t interval;
    uint32_t now;
    uint32_t then;
    uint32_t delta;
    int32_t left;
    bool catchup;
};

#endif /* TIMER_HPP */