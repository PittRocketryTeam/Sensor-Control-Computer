#include "board.hpp"
#include "Logger.hpp"
#include "Error.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{
    
}

bool Logger::init()
{
    // Initialize RTC
    /*setSyncProvider(getTeensy3Time);
    delay(100);
    RTC_set_successfully = (timeStatus() == timeSet);*/

    //generateFilename();  // Generate unique log filename

    int i;
    for (i = 0; i < CONN_ATTEMPTS; ++i)
    {
        Error::on(LOG_INIT);
        
        // pin mapping magic
        SPI.setMOSI(7);
        SPI.setMISO(8);
        int status = SD.begin(62);
        
        if (status)
        {
            break;
        }

        // fail

        delay(CONN_DELAY);
    }

    Error::off();
    if (i == CONN_ATTEMPTS)
    {
        Serial.println("fail");
        Error::display(LOG_INIT, FATAL);
        Error::display(WERE_SCREWED, FATAL);
    }

    genUniqueFn();

    handle = SD.open(filename, FILE_WRITE);

    return true;
}

void Logger::generateFilename()
{
    memset(filename, 0, sizeof(filename));

    /*current_time = now();
    if (RTC_set_successfully)
    {
        sprintf(filename, "%d-%d-%d_%d-%d-%d.csv", 
                month(current_time),
                day(current_time),
                year(current_time),
                hour(current_time),
                minute(current_time),
                second(current_time)
               );        
    }
    else
    {
        sprintf(filename, "loggylog.csv");
    }*/
    sprintf(filename, "loggylog.csv");
}

void Logger::genUniqueFn()
{
    int log_num = 1;

    if (SD.exists("log_journal"))
    {
        handle = SD.open("log_journal", FILE_READ);
        delay(100);
        char bf[100];
        size_t r = handle.readBytes(bf, 100);
        delay(100);
        bf[r] = '\0';
        log_num = atoi(bf);
        
        handle.close();
        delay(100);
    }

    handle = SD.open("log_journal", FILE_WRITE);
    delay(100);
    handle.printf("%d", log_num);
    delay(100);
    handle.flush();
    delay(100);
    handle.close();
    delay(100);

    memset(filename, 0, sizeof(filename));
    sprintf(filename, "loggylog_%d.csv", log_num);

    delay(100);
}

bool Logger::writeToMemory(Data data)
{
    if (!handle)
    {
        return false;
    }

    handle.printf("%ld, ,%f,%f,%f, ,%f,%f,%f,%f, ,%f,%f,%f, ,%f,%f,%f, ,%f,\n",
            data.timestamp,

            data.altimeterData.temperature, 
            data.altimeterData.pressure, 
            data.altimeterData.altitude,
            
            // data.gpsData.time, 
            data.gpsData.latitude, 
            // data.gpsData.lat_direction, 
            data.gpsData.longitude, 
            // data.gpsData.long_direction, 
            // data.gpsData.fix_quality, 
            data.gpsData.number_of_satellites, 
            // data.gpsData.hdop, 
            data.gpsData.altitude, 
            // data.gpsData.rssi,
            
            // data.healthData.main_battery_temperature, 
            // data.healthData.main_battery_voltage, 
            // data.healthData.reg_5V_battery_temperature, 
            // data.healthData.reg_5V_battery_voltage, 
            // data.healthData.reg_3V3_battery_temperature, 
            // data.healthData.reg_3V3_battery_voltage,
            
            data.imuData.euler_abs_orientation_x, 
            data.imuData.euler_abs_orientation_y, 
            data.imuData.euler_abs_orientation_z,

            data.imuData.acceleration_x,
            data.imuData.acceleration_y,
            data.imuData.acceleration_z,

            data.healthData.main_battery_voltage
            
           // data.photocellData.brightness
    );

    return true; 
}

void Logger::flush()
{
    if (!handle)
    {
        return;
    }
    handle.flush();
}

void Logger::reopen()
{
    if (!handle)
    {
        handle = SD.open(filename, FILE_WRITE);
    }
}

void Logger::close()
{
    if (handle.isOpen())
    {
        handle.flush();
        handle.close();
    }
}

time_t Logger::getTeensy3Time()
{
    return Teensy3Clock.get();
}