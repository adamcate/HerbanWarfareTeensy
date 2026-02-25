#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <chrono>

typedef struct dir_s
{
    float x;
    float y;
    float z;
}dir;

struct IMU
{
    Adafruit_ICM20948 icm;
    uint16_t delay_us = 65535;
    bool initialized = false;
    float dT = 0.f;

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t magnet;
    sensors_event_t temp;

    dir direction{};

    IMU(uint16_t delay_us, float dT);

    const sensors_vec_t *acc();

    const sensors_vec_t *gyr();
    
    const float tmp();

    const sensors_vec_t *mag();

    void Update();
    void printStatus();
};

