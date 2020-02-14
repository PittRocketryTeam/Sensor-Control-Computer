#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__


/******************************** GENERAL *********************************/

#define VERBOSE 1

/******************************** MAIN *********************************/

#define MODE_IDLE 0
#define MODE_STARTUP 1
#define MODE_FLIGHT 2

/******************************** HEALTH *********************************/

#define MOHM 1e6
#define KOHM 1e3

#define THERMISTOR_T0 298.15
#define THERMISTOR_BETA 3380.0

#define ANALOG_MAX 1023

/******************************** ALTIMETER *********************************/

#define SEALEVELPRESSURE_HPA 1013.25

/******************************** GPS *********************************/

#define GPSECHO false

/******************************** ERROR *********************************/

#define ERROR_DELAY 200
#define CONN_ATTEMPTS 5
#define CONN_DELAY 500

typedef enum 
{
    SERIAL_INIT = 1, 
    LOG_INIT = 2, 
    IMU_INIT = 3, 
    ALT_INIT = 4, 
    GPS_INIT = 5, 
    TX_INIT = 6, 
    WERE_SCREWED = 7
} errcode_t;

typedef enum 
{
    WARN, 
    FATAL
} errtype_t;

/******************************** LOGGER *********************************/

#define MAX_SENSORS 20


#endif /* __CONSTANTS_HPP__ */
