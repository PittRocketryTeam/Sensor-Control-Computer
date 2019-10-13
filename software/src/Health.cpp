#include "Health.hpp"

Health::Health() :
    Sensor(),
    battery_temperature(-1),
    battery_voltage(-1),
    reg5_voltage(-1),
    reg3_voltage(-1)
{

}

Health::~Health()
{

}

bool Health::init()
{
    pinMode(TB_PIN, INPUT);
    pinMode(VB_PIN, INPUT);
    pinMode(V5_PIN, INPUT);
    pinMode(V3_PIN, INPUT);
    return true;
}


Data Health::read(Data data)
{
    if (!enabled)
    {
        return data;
    }

    data.healthData.main_battery_temperature = battery_temperature;
    data.healthData.main_battery_voltage = battery_voltage;
    data.healthData.reg_5V_battery_voltage = reg5_voltage;
    data.healthData.reg_3V3_battery_voltage = reg3_voltage;
    // TODO: Set data.healthData.5V_reg_battery_temperature
    // TODO: Set data.healthData.5V_reg_battery_voltage
    // TODO: Set data.healthData.3V3_reg_battery_temperature
    // TODO: Set data.healthData.3V3_reg_battery_voltage

    return data;
}

Data Health::poll(Data data)
{
    if (!enabled)
    {
        return data;
    }

    int battery_t_raw = analogRead(TB_PIN);
    int battery_v_raw = analogRead(VB_PIN);
    int reg5_v_raw = analogRead(V5_PIN);
    int reg3_v_raw = analogRead(V3_PIN);

    battery_temperature = calculate_temperature(battery_t_raw, 3380.0);
    battery_voltage = calculate_voltage(battery_v_raw, VBR1, VBR2);
    reg5_voltage = calculate_voltage(reg5_v_raw, V5R1, V5R2);
    reg3_voltage = calculate_voltage(reg3_v_raw, V3R1, V3R2);

    return read(data);
}

void Health::enable()
{
    enabled = true;
}

void Health::disable()
{
    enabled = false;
}

float Health::calculate_voltage(int raw, int r1, int r2)
{
    float cr = ((float)r2 / (float)(r1 + r2));
    return raw * (3.3 / (float)ANALOG_MAX) * (1.0 / cr);
}

float Health::calculate_temperature(int raw, float beta)
{
    float k = 1.0 / ((1.0 / T0) + (1.0 / beta) * (log((float)ANALOG_MAX / (float)raw) - 1.0));
    return k - 273.15;
}
