#ifndef CMOTOR_H
#define CMOTOR_H

#include <iostream>
#include "pigpio.h"

class CMotor
{
public:
    CMotor();
    ~CMotor();

    // Movement
    void mov_Forward(int speed);
    void mov_Backward(int speed);
    void mov_Right(int speed);
    void mov_Left(int speed);
    void mov_Stop();


private:

    #define AI1 2 // PIN 3
    #define AI2 22 // PIN 15
    #define BI1 11 // PIN 23
    #define BI2 17 // PIN 11
    #define STBY 1 // PIN 28
    #define PWMA 10 // PIN 19
    #define PWMB 15 // PIN 10
};

#endif // CMOTOR_H
