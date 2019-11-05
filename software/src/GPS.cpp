#include "GPS.hpp"
// #include "Adafruit_GPS.h"

#define GPSECHO false
uint32_t timer = millis();


GPS::GPS() : 
    Sensor(), 
    time(0), 
    lat(0), 
    lat_direction(0),
    lon(0), 
    long_direction(0), 
    fix_quality(0), 
    number_of_satellites(0), 
    hdop(0), 
    alt(0),
    rssi(0)
{
}
    
GPS::~GPS() {}

bool GPS::init()
{
    Serial.println("Initializing GPS"); 

    gps = Adafruit_GPS(&Serial1);
    
    pinMode(VIN_PIN, OUTPUT);

Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  gps.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  gps.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);






    return true;
}

Data GPS::read(Data data)
{
    data.gpsData.time = time;
    // Serial.println((String) "Time: " + time); 

    data.gpsData.latitude = lat;
    //Serial.println( "Latitude: " + latitude); 
    
    data.gpsData.lat_direction = lat_direction;
    // Serial.println((String)"Latitude direction: " + lat_direction); 

    data.gpsData.longitude = lon;
    // Serial.println((String) "Longitude: " + longitude); 

    data.gpsData.long_direction = long_direction;
    // Serial.println((String)"Longitude direction: " + long_direction); 

    data.gpsData.fix_quality = fix_quality;
    // Serial.println((String)"Fix quality: " + fix_quality); 

    data.gpsData.number_of_satellites = number_of_satellites;
    // Serial.println((String) "Number of satellites: " + number_of_satellites); 

    data.gpsData.hdop = hdop;   //Horizontal Dilution of Precision. Describes the strength of the current satellite configuration, or geometry, on the accuracy of the data collected by a GPS at the time of use
    // Serial.println((String) ": " + hdop); 

    data.gpsData.altitude = alt;
    // Serial.println((String) "Altitude: " + altitude); 

    data.gpsData.rssi = rssi;   //Received signal strength indicator is a measurement of the power present in a received radio signal. 
    // Serial.println((String) "RSSI: " + rssi); 
    
    return data;
}

Data GPS::poll(Data data)
{
    // int time = 0;
    // float latitude = 0;
    // int lat_direction = 0;
    // float longitude = 0;
    // int long_direction = 0; 
    // int fix_quality = 0; 
    // int number_of_satellites = 0; 
    // int hdop = 0; 
    // int altitude = 0; 
    // int rssi = 0;  

      // read data from the GPS in the 'main loop'
  char c = gps.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (gps.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.println(gps.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!gps.parse(gps.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return data; // we can fail to parse a sentence in which case we should just wait for another
  }
  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis()) timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    if (gps.hour < 10) { Serial.print('0'); }
    Serial.print(gps.hour, DEC); Serial.print(':');
    if (gps.minute < 10) { Serial.print('0'); }
    Serial.print(gps.minute, DEC); Serial.print(':');
    if (gps.seconds < 10) { Serial.print('0'); }
    Serial.print(gps.seconds, DEC); Serial.print('.');
    if (gps.milliseconds < 10) {
      Serial.print("00");
    } else if (gps.milliseconds > 9 && gps.milliseconds < 100) {
      Serial.print("0");
    }
    // Serial.println(GPS.milliseconds);
    // Serial.print("Date: ");
    // Serial.print(GPS.day, DEC); Serial.print('/');
    // Serial.print(GPS.month, DEC); Serial.print("/20");
    // Serial.println(GPS.year, DEC);
    // Serial.print("Fix: "); Serial.print((int)GPS.fix);
    // Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    // if (GPS.fix) {
    //   Serial.print("Location: ");
    //   Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
    //   Serial.print(", ");
    //   Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
    //   Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    //   Serial.print("Angle: "); Serial.println(GPS.angle);
    //   Serial.print("Altitude: "); Serial.println(GPS.altitude);
    //   Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    // }
  }





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
    

    Serial.println("GPS disabled.");
    
    // gps.standby(); 

    digitalWrite(VIN_PIN, LOW);   
}

