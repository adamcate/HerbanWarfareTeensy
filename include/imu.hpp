#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

struct IMU
{
    Adafruit_ICM20948 icm;
    uint16_t delay_us = 65535;
    bool initialized = false;

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t magnet;
    sensors_event_t temp;

    IMU(uint16_t delay_us);

    void Update();

    const sensors_vec_t *acc();

    const sensors_vec_t *gyr();
    
    const float tmp();

    const sensors_vec_t *mag();
};

