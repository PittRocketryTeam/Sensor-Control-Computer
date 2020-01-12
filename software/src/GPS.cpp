#include "GPS.hpp"

#define GPSECHO false

GPS::GPS() :
    Sensor(),
    my_time(0),
    my_lat(0),
    my_lat_direction(0),
    my_lon(0),
    my_long_direction(0),
    my_fix_quality(0),
    my_number_of_satellites(0),
    my_hdop(0),
    my_alt(0),
    my_rssi(0)
{
}

GPS::~GPS()
{

}

bool GPS::init()
{
    Serial.println("Initializing GPS");

    gps = Adafruit_GPS(&Serial2);

    // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
    gps.begin(9600);
    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // uncomment this line to turn on only the "minimum recommended" data
    //gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
    // the parser doesn't care about other sentences at this time
    // Set the update rate
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    // For the parsing code to work nicely and have time to sort thru the data, and
    // print it out we don't suggest using anything higher than 1 Hz

    // Request updates on antenna status, comment out to keep quiet
    gps.sendCommand(PGCMD_ANTENNA);

    delay(1000);

    return true;
}

Data GPS::read(Data data)
{
    data.gpsData.time = my_time;
    data.gpsData.latitude = my_lat;
    data.gpsData.lat_direction = my_lat_direction;
    data.gpsData.longitude = my_lon;
    data.gpsData.long_direction = my_long_direction;
    data.gpsData.fix_quality = my_fix_quality;
    data.gpsData.number_of_satellites = my_number_of_satellites;
    data.gpsData.hdop = my_hdop;
    data.gpsData.altitude = my_alt;
    data.gpsData.rssi = my_rssi; 

    return data;
}

Data GPS::poll(Data data)
{
    char c = gps.read();
    (void)c;

    if (gps.newNMEAreceived())
    {
        gps.parse(gps.lastNMEA());
    }

    my_fix_quality = gps.fixquality;
    my_time = gps.seconds;
    my_number_of_satellites = gps.satellites;
    my_lat = gps.latitude;
    my_lon = gps.longitude;
    my_alt = gps.altitude;
    my_rssi = atoi(gps.lastNMEA());
    my_hdop = gps.HDOP;

    return read(data);
}

void GPS::enable()
{

    Serial.println("GPS enabled.");

    // gps.wakeup();

    digitalWrite(VIN_PIN, HIGH);
}

void GPS::disable()
{
    // pin is pulled to ground, it will turn off the GPS module
    // if you disable it, you will lose your fix and it will
    // take a long time to get fix back if you dont have backup battery

    // gps.standby();

    digitalWrite(VIN_PIN, LOW);
}
