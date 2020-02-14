#include "Health.hpp"

Health::Health() :
    Sensor(),
    battery_temperature(-1),
    battery_voltage(-1),
    reg5_voltage(-1),
    reg3_voltage(-1),
    enabled(true)
{

}

Health::~Health()
{

}

bool Health::init()
{
    analogReadResolution(10);
    analogReference(0);
    pinMode(BATT_T, INPUT);
    pinMode(BATT_V, INPUT);
    pinMode(REG5_V, INPUT);
    pinMode(REG3_V, INPUT);
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

    if (VERBOSE)
    {
        Serial.printf("Health::read() - main_battery_temperature: %lf\n",
            data.healthData.main_battery_temperature);
        Serial.printf("Health::read() - main_battery_voltage: %lf\n", 
            data.healthData.main_battery_voltage);
        Serial.printf("Health::read() - reg_5V_battery_voltage: %lf\n",
            data.healthData.reg_5V_battery_voltage);
        Serial.printf("Health::read() - reg_3V3_battery_voltage: %lf\n", 
            data.healthData.reg_3V3_battery_voltage);
    }

    return data;
}

Data Health::poll(Data data)
{
    if (!enabled)
    {
        return data;
    }

    int battery_t_raw = analogRead(BATT_T);
    int battery_v_raw = analogRead(BATT_V);
    int reg5_v_raw = analogRead(REG5_V);
    int reg3_v_raw = analogRead(REG3_V);

    (void)battery_t_raw; // squash pesky warnings

    battery_temperature = calculate_temperature(battery_t_raw, THERMISTOR_BETA);
    battery_voltage = calculate_voltage(battery_v_raw, MOHM, .470 * MOHM);
    reg5_voltage = calculate_voltage(reg5_v_raw, MOHM, MOHM);
    reg3_voltage = calculate_voltage(reg3_v_raw, MOHM, MOHM);

    if (VERBOSE)
    {
        Serial.printf("Health::poll() - main_battery_temperature: %lf\n",
            data.healthData.main_battery_temperature);
        Serial.printf("Health::poll() - main_battery_voltage: %lf\n", 
            data.healthData.main_battery_voltage);
        Serial.printf("Health::poll() - reg_5V_battery_voltage: %lf\n",
            data.healthData.reg_5V_battery_voltage);
        Serial.printf("Health::poll() - reg_3V3_battery_voltage: %lf\n", 
            data.healthData.reg_3V3_battery_voltage);
    }

    return read(data);
}

void Health::enable()
{
    if (VERBOSE) { Serial.println("Health::enable() - health enabled\n"); }
    enabled = true;
}

void Health::disable()
{
    if (VERBOSE) { Serial.println("Health::disable() - health disabled\n"); }
    enabled = false;
}

float Health::calculate_voltage(int raw, float r1, float r2)
{
    float vout = 5 * ((float)raw / (float)ANALOG_MAX);
    return (vout * (float)(r1 + r2)) / (float)r2;
}

float Health::calculate_temperature(int raw, float beta)
{
    float k = 1.0 / ((1.0 / THERMISTOR_T0) + (1.0 / beta) * (log((float)ANALOG_MAX / (float)raw) - 1.0));
    return k - 273.15;
}
