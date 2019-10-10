#include "Health.hpp"

Health::Health() :
    Sensor()
{

}

Health::~Health()
{

}

bool Health::init()
{
    return false;
}


Data Health::read(Data data)
{
    // TODO: Set data.healthData.main_battery_temperature
    // TODO: Set data.healthData.main_battery_voltage
    // TODO: Set data.healthData.5V_reg_battery_temperature
    // TODO: Set data.healthData.5V_reg_battery_voltage
    // TODO: Set data.healthData.3V3_reg_battery_temperature
    // TODO: Set data.healthData.3V3_reg_battery_voltage

    return data;
}

Data Health::poll(Data data)
{
    // TODO: Set data.healthData.main_battery_temperature
    // TODO: Set data.healthData.main_battery_voltage
    // TODO: Set data.healthData.5V_reg_battery_temperature
    // TODO: Set data.healthData.5V_reg_battery_voltage
    // TODO: Set data.healthData.3V3_reg_battery_temperature
    // TODO: Set data.healthData.3V3_reg_battery_voltage
    
    return data;
}

void Health::enable()
{

}

void Health::disable()
{

}
