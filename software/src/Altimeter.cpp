#include "Altimeter.hpp"


Altimeter::Altimeter() :    
    Sensor(),
    baselinePressure(SEALEVELPRESSURE_HPA)
{

}

Altimeter::~Altimeter()
{

}

bool Altimeter::init()
{
    bool success = false;

    int i;
    for (i=0; i < CONN_ATTEMPTS; i++)
    {
        Error::on(ALT_INIT);
        if (bmp.begin())
        {
            break;
            success = true;
        }

        delay(CONN_DELAY);
    }
    Error::off();
    if (i > CONN_ATTEMPTS)
    {
        Error::display(ALT_INIT, FATAL);
    }

    if (success && VERBOSE) { Serial.println("Altimeter::init() - successful init\n"); }

    return success;
}

Data Altimeter::read(Data data)
{
    data.altimeterData.temperature = bmp.temperature;
    data.altimeterData.pressure = bmp.pressure;

    // doesn't performReading again, altitude is just calculated 
    // from the pressure and the ground level pressure set earlier
    data.altimeterData.altitude = bmp.readAltitude(baselinePressure);

    return data;
}

Data Altimeter::poll(Data data)
{
    if(!bmp.performReading()) // assign values to pressure and temperature
    {
        if (VERBOSE) { Serial.println("Failed to perform reading :("); } 
    }

    data.altimeterData.temperature = bmp.readTemperature();
    data.altimeterData.pressure = bmp.readPressure();
    data.altimeterData.altitude = bmp.readAltitude(baselinePressure);
    
    if (VERBOSE) 
    { 
        Serial.printf("temp: %f\npressure: %f\nalt: %f\n", 
            data.altimeterData.temperature, 
            data.altimeterData.pressure, 
            data.altimeterData.altitude); 
    }
    
    return data;
}

void Altimeter::enable()
{
    bmp_dev->settings.op_mode = BMP3_NORMAL_MODE;
    if(bmp3_set_op_mode(bmp_dev) != 0)
    {
        if (VERBOSE) { Serial.println("Altimeter failed to enable"); }
    }
}

void Altimeter::disable()
{
    bmp_dev->settings.op_mode = BMP3_SLEEP_MODE;
    if(bmp3_set_op_mode(bmp_dev) != 0)
    {
        if (VERBOSE) { Serial.println("Altimeter failed to disable"); }
    }
        
}