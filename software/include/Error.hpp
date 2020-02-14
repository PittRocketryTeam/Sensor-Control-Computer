#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include "Sensor.hpp"
#include "board.hpp"
#include "constants.hpp"
#include <Arduino.h>


class Error
{
public:

    static bool init();
    static void display(int, errtype_t);
    static void reset(int);
    static void summary();
    static void success();
    static void on(int);
    static void off();

private:
    static void on();

    static int b0;
    static int b1;
    static int b2;

    static int leds[];

    static int accumulated[8];
    static int clean;
};

#endif // __ERROR_HPP__
