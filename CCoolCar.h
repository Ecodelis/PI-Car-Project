#ifndef CCOOLCAR_H
#define CCOOLCAR_H

//#include "CControl.h"
#include "CCommunication.h"
#include "CMotor.h"
#include "CGuidance.h"

#include "pigpio.h"
//#include "cvui.h"

#include <ncurses.h>
#include <regex>
#include <mutex>
#include <thread>
#include <string>


class CCoolCar
{
public:
    CCoolCar(int version);
    ~CCoolCar();
    void Automotive_Software();
    void system_Control();
    void initGPIO();
    void destroyGPIO();
    void run();


private:
    //CControl _controlPI;
    CCommunication _commPI;
    CMotor _motorPI;
    CGuidance _guidePI;

    std::thread _engine;
    int handler_SPI;
    bool _loop;

    #define AI1 2 // PIN 3
    #define AI2 22 // PIN 15
    #define BI1 11 // PIN 23
    #define BI2 17 // PIN 11
    #define STBY 1 // PIN 28
    #define PWMA 10 // PIN 19
    #define PWMB 15 // PIN 10

    #define LED1 25 // PIN 22
    #define LED2 8 // PIN 24
    #define LED3 7 // PIN 26

};

#endif // CCOOLCAR_H