#ifndef MOTORS_HPP
#define MOTORS_HPP

#include <stdint.h>
#include <Arduino.h>

#define MOTOR_ENABLE_1 6
#define MOTOR_ENABLE_2 10
#define MOTOR_DIR_1 7
#define MOTOR_DIR_2 8
#define MOTOR_DIR_3 11
#define MOTOR_DIR_4 12

struct Motor
{
    float pwm_left = 0; float pwm_right = 0;
    // bool switch_lr = false;
    Motor()
    {
        pinMode(MOTOR_ENABLE_1, OUTPUT);
        pinMode(MOTOR_ENABLE_2, OUTPUT);
        pinMode(MOTOR_DIR_1, OUTPUT);
        pinMode(MOTOR_DIR_2, OUTPUT);
        pinMode(MOTOR_DIR_3, OUTPUT);
        pinMode(MOTOR_DIR_4, OUTPUT);
    }

    void Drive(float left, float right)
    {
        left = -left; right = -right; // make it so that positive values actually reflect forward movement lol
        bool dirL = true; bool dirR = true;
        if(left < 0.f) 
        {
            left = -left;
            dirL = false; 
        }
        if(right < 0.f) 
        {
            right = -right;
            dirR = false;
        }
        analogWrite(MOTOR_ENABLE_1, (int)left);
        if(dirL){
            digitalWrite(MOTOR_DIR_1, HIGH);
            digitalWrite(MOTOR_DIR_2, LOW);
        }else{
            digitalWrite(MOTOR_DIR_1, LOW);
            digitalWrite(MOTOR_DIR_2, HIGH);
        }

        analogWrite(MOTOR_ENABLE_2, (int)right);
        if(dirR){
            digitalWrite(MOTOR_DIR_3, HIGH);
            digitalWrite(MOTOR_DIR_4, LOW);
        }else{
            digitalWrite(MOTOR_DIR_3, LOW);
            digitalWrite(MOTOR_DIR_4, HIGH);
        }
        
    }
};

#endif