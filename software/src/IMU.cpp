#include "IMU.hpp"

IMU::IMU()
{
    sensor = Adafruit_BNO055(55, IMU_ADDR, &Wire1);
    ax = 0.0f;
    ay = 0.0f;
    az = 0.0f;
    ox = 0.0f;
    oy = 0.0f;
    oz = 0.0f;
}

IMU::~IMU()
{

}

bool IMU::init()
{
    int i;
    for (i = 0; i < CONN_ATTEMPTS; ++i)
    {
        Error::on(IMU_INIT);
        if (sensor.begin())
        {
            break;
        }

        if (VERBOSE) { Serial.println("No BNO055 detected ... Check your wiring or I2C ADDR!"); }
        delay(CONN_DELAY);
    }
    Error::off();
    if (i >= CONN_ATTEMPTS)
    {
        if (VERBOSE) 
        { 
            Serial.printf("IMU::init() - After %d attempts failed to initialize\n", CONN_ATTEMPTS); 
        }
        Error::display(IMU_INIT, FATAL);
    }

    sensor.setExtCrystalUse(true);

    enable();

    return false;
}

Data IMU::read(Data data)
{
    data.imuData.euler_abs_orientation_x = ox;
    data.imuData.euler_abs_orientation_y = oy;
    data.imuData.euler_abs_orientation_z = oz;

    data.imuData.acceleration_x = ax;
    data.imuData.acceleration_y = ay;
    data.imuData.acceleration_z = az;

    if (VERBOSE)
    {
        Serial.printf("IMU::read() - euler_abs_orientation_x: %lf\n",
            data.imuData.euler_abs_orientation_x);
        Serial.printf("IMU::read() - euler_abs_orientation_y: %lf\n", 
            data.imuData.euler_abs_orientation_y);
        Serial.printf("IMU::read() - euler_abs_orientation_z: %lf\n",
            data.imuData.euler_abs_orientation_z);

        Serial.printf("IMU::read() - acceleration_x: %lf\n", 
            data.imuData.acceleration_x);
        Serial.printf("IMU::read() - acceleration_y: %lf\n", 
            data.imuData.acceleration_y);
        Serial.printf("IMU::read() - acceleration_z: %lf\n", 
            data.imuData.acceleration_z);
    }

    return data;
}

Data IMU::poll(Data data)
{
    sensor.getEvent(&event);

    o = sensor.getVector(Adafruit_BNO055::VECTOR_EULER);
    ox = (float)o.x();
    oy = (float)o.y();
    oz = (float)o.z();

    a = sensor.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    ax = (float)a.x();
    ay = (float)a.y();
    az = (float)a.z();

    if (VERBOSE)
    {
        Serial.printf("IMU::poll() - euler_abs_orientation_x: %lf\n",
            data.imuData.euler_abs_orientation_x);
        Serial.printf("IMU::poll() - euler_abs_orientation_y: %lf\n", 
            data.imuData.euler_abs_orientation_y);
        Serial.printf("IMU::poll() - euler_abs_orientation_z: %lf\n",
            data.imuData.euler_abs_orientation_z);

        Serial.printf("IMU::poll() - acceleration_x: %lf\n", 
            data.imuData.acceleration_x);
        Serial.printf("IMU::poll() - acceleration_y: %lf\n", 
            data.imuData.acceleration_y);
        Serial.printf("IMU::poll() - acceleration_z: %lf\n", 
            data.imuData.acceleration_z);
    }

    return read(data);
}

void IMU::enable()
{
    if (VERBOSE) { Serial.println("IMU::enable() - imu enabled"); }

    sensor.enterNormalMode();
}

void IMU::disable()
{
    if (VERBOSE) { Serial.println("IMU::disable() - imu disabled"); }

    sensor.enterSuspendMode();
}
