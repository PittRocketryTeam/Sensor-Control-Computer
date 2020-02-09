#ifndef ERROR_HPP
#define ERROR_HPP

#define DEBUG_LED_1 A22
#define DEBUG_LED_2 13
#define DEBUG_LED_3 39

#define ERROR_DELAY 200
#define CONN_ATTEMPTS 5
#define CONN_DELAY 500

#include "Sensor.hpp"

typedef enum {SERIAL_INIT = 1, LOG_INIT = 2, IMU_INIT = 3, ALT_INIT = 4, GPS_INIT = 5, TX_INIT = 6, WERE_SCREWED = 7} errcode_t;
typedef enum {WARN, FATAL} errtype_t;

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

#endif /* ERROR_HPP */
