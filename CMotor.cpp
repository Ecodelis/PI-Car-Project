#include "CMotor.h"

// speed is 0 to 255
void CMotor::mov_Forward(int speed)
{
    gpioPWM(PWMA, speed);
    gpioPWM(PWMB, speed);

    gpioWrite(AI1, 0);
    gpioWrite(AI2, 1);

    gpioWrite(BI1, 0);
    gpioWrite(BI2, 1);

    std::cout << "\n[F]";
}

void CMotor::mov_Backward(int speed)
{
    gpioPWM(PWMA, speed);
    gpioPWM(PWMB, speed);

    gpioWrite(AI1, 1);
    gpioWrite(AI2, 0);
    gpioWrite(BI1, 1);
    gpioWrite(BI2, 0);

    std::cout << "\n[B]" + speed;
}

void CMotor::mov_Right(int speed)
{
    gpioWrite(STBY, 1);

    gpioPWM(PWMA, speed);
    gpioPWM(PWMB, speed);

    gpioWrite(AI1, 1);
    gpioWrite(AI2, 0);

    gpioWrite(BI1, 0);
    gpioWrite(BI2, 1);

    std::cout << "\n[R]";
}

void CMotor::mov_Left(int speed)
{


    gpioPWM(PWMA, speed);
    gpioPWM(PWMB, speed);

    gpioWrite(AI1, 0);
    gpioWrite(AI2, 1);
    gpioWrite(BI1, 1);
    gpioWrite(BI2, 0);

    std::cout << "\n[L]";
}

void CMotor::mov_Stop()
{
    gpioPWM(PWMA, 0);
    gpioPWM(PWMB, 0);

    gpioWrite(AI1, 0);
    gpioWrite(AI2, 0);
    gpioWrite(BI1, 0);
    gpioWrite(BI2, 0);

    //std::cout << "Stop...\n";
}

CMotor::CMotor()
{
    gpioWrite(STBY, 1);
}

CMotor::~CMotor()
{
    gpioWrite(STBY, 0);
}
