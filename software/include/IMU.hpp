#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "Sensor.hpp"

#define I2C_ADDR 0x28

typedef struct ImuData
{
    // Absolute Orientation (Euler Vector, 100Hz) Three axis orientation data based on a 360° sphere
    float euler_abs_orientation_x;
    float euler_abs_orientation_y;
    float euler_abs_orientation_z;
    
    // Absolute Orientation (Quatenrion, 100Hz) Four point quaternion output for more accurate data manipulation
    float quaternion_abs_orientation_x;
    float quaternion_abs_orientation_y;
    float quaternion_abs_orientation_z;
    
    // Angular Velocity Vector (100Hz) Three axis of 'rotation speed' in rad/s
    float angular_velocity_x;
    float angular_velocity_y;
    float angular_velocity_z;

    // Acceleration Vector (100Hz) Three axis of acceleration (gravity + linear motion) in m/s^2
    float acceleration_x;
    float acceleration_y;
    float acceleration_z;

    // Magnetic Field Strength Vector (20Hz) Three axis of magnetic field sensing in micro Tesla (uT)
    float magnetic_field_strength_x;
    float magnetic_field_strength_y;
    float magnetic_field_strength_z;

    // Linear Acceleration Vector (100Hz) Three axis of linear acceleration data (acceleration minus gravity) in m/s^2
    float linear_acceleration_x;
    float linear_acceleration_y;
    float linear_acceleration_z;

    // Gravity Vector (100Hz) Three axis of gravitational acceleration (minus any movement) in m/s^2
    float gravity_x;
    float gravity_y;
    float gravity_z;

    // Temperature (1Hz) Ambient temperature in degrees celsius
    float temperature;
} ImuData;

class IMU : public Sensor<ImuData>
{
    public:

        IMU();
        ~IMU();
        
        bool init() override;
        ImuData read() override;
        ImuData poll() override;
        void enable() override;
        void disable() override;
};

#endif
// __IMU_HPP__