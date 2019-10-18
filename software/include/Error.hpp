#ifndef ERROR_HPP
#define ERROR_HPP

#define DEBUG_LED_1 0
#define DEBUG_LED_2 0
#define DEBUG_LED_3 0

#include "Sensor.hpp"

typedef enum {SERIAL_INIT = 1, LOG_INIT = 2, IMU_INIT = 3, ALT_INIT = 4, GPS_INIT = 5, TX_INIT = 6, WERE_SCREWED = 7} errcode_t;
typedef enum {WARN, FATAL} errtype_t;

class Error
{
public:
    Error();
    ~Error();

    bool init();
    void display(errcode_t, errtype_t);

private:
    void on();
    void off();
    int b0;
    int b1;
    int b2;
};

#endif /* ERROR_HPP */