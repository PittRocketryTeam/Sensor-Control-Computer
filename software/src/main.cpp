#include <Arduino.h>
#include "Data.hpp"
#include "Altimeter.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"
#include "Error.hpp"

IMU gyro(true);
Altimeter alt;
Logger logger;

Data state;

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;

void ready();
void armed();

void setup()
{
    Error::init();
    
    logger.init();

    Error::success();
}

void loop()
{
    Error::summary();
}
