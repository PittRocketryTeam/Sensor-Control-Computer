#ifndef __BOARD_HPP__
#define __BOARD_HPP__

/******************************** HEALTH *********************************/

#define PHOTOCELL_PIN 34
#define THERMISTOR_PIN 35

#define BATT_T A3
#define BATT_V A1
#define REG5_V A8
#define REG3_V A7

/******************************** ALTIMETER *********************************/

#define ALTIMETER_SCL 19
#define ALTIMETER_SDA 18
#define IMU_ADDR 0X28

/******************************** GPS *********************************/

#define GPS_SERIAL Serial2
#define GPS_ENABLE 0

/******************************** ERROR *********************************/

#define DEBUG_LED_1 A22
#define DEBUG_LED_2 13
#define DEBUG_LED_3 39

/******************************** XBEE *********************************/

#define XBEE_SERIAL Serial1

/******************************** LOGGER *********************************/

#define BUILTIN_SDCARD 254


#endif /* __BOARD_HPP__ */
