#include "Altimeter.hpp"
#include "Adafruit_BMP3XX.h"

#define cspin 2

Adafruit_BMP3XX bmp;//inits for i2c - defaults to 0x77 address and "Wire"
float initAlt;

Altimeter::Altimeter() :
    Sensor()
{
    initAlt = -1;//indicates we haven't read the ground pressure yet
}

bool Altimeter::init()
{
    if(!bmp.begin())
    {
        Serial.println("Couldn't init altimeter!");
        while(1);
        return false;
    } else
return true;
}

Data Altimeter::read(Data data)
{
    // TODO: Set data.altimeterData.temperature
    data.altimeterData.temperature = bmp.readTemperature();
    // TODO: Set data.altimeterData.pressure
    data.altimeterData.pressure = bmp.readPressure();
    // TODO: Set data.altimeterData.altitude
    if(initAlt == -1)//case where initAlt isn't set -- haven't hit button on ground control yet to indicate we're ready to launch
        Serial.println("Cannot poll altitude --- ground pressure not yet set!");
    else
        data.altimeterData.altitude = bmp.readAltitude(initAlt);

    return data;

    return data;
}

Data Altimeter::poll(Data data)
{
    if (!bmp.performReading()) {
        Serial.println("Failed to perform reading :(");
    }
    // TODO: Set data.altimeterData.temperature
    //data.altimeterData.temperature = bmp.readTemperature();
    // TODO: Set data.altimeterData.pressure
    //data.altimeterData.pressure = bmp.readPressure();
    // TODO: Set data.altimeterData.altitude
    //if(initAlt == -1)//case where initAlt isn't set -- haven't hit button on ground control yet to indicate we're ready to launch
    //    Serial.println("Cannot poll altitude --- ground pressure not yet set!");
    //else
    //    data.altimeterData.altitude = bmp.readAltitude(initAlt);

    return data;
}

void Altimeter::enable()
{

}

void Altimeter::disable()
{

}

void Altimeter::setBaselinePressure()
{
    initAlt = bmp.readPressure();
}

