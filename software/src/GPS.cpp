#include "GPS.hpp"
#include "board.hpp"
#include "Error.hpp"

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
    pinMode(GPS_ENABLE, OUTPUT);

    gps = Adafruit_GPS(&GPS_SERIAL);

    // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
    int err = 0;
    while (!gps.begin(9600))
    {
        Error::display(GPS_INIT, WARN);
        err++;
        delay(100);

        if (err > 10)
        {
            Error::display(GPS_INIT, FATAL);
            break;
        }
    }
    
    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    
    // uncomment this line to turn on only the "minimum recommended" data
    //gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

    // Set the update rate
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

    // Request updates on antenna status, comment out to keep quiet
    gps.sendCommand(PGCMD_ANTENNA);

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
    digitalWrite(GPS_ENABLE, HIGH);
}

void GPS::disable()
{
    digitalWrite(GPS_ENABLE, LOW);
}
