#ifndef CCOMMUNICATION_H
#define CCOMMUNICATION_H

#include <thread>
#include <string>

#include "CServer.h"
#include "CControl.h"
#include "pigpio.h"

class CCommunication
{
public:
    // Important Class Methods
    CCommunication();
    ~CCommunication();
    void server_start(CServer*, int port);
    void S1(); // serverCOMP
    void check();

    // Checking (getter) Class Methods
    bool getForward() {return Forward;}
    bool getRight() {return Right;}
    bool getLeft() {return Left;}
    bool getBackward() {return Backward;}
    bool getStop() {return Stop;}

    bool getLED1() {return LED1;}
    bool getLED2() {return LED2;}
    bool getLED3() {return LED3;}

    // Setter Methods
    void setForward(bool boolean) {Forward = boolean;}
    void setRight(bool boolean) {Right = boolean;}
    void setLeft(bool boolean) {Left = boolean;}
    void setBackward(bool boolean) {Backward = boolean;}
    void setStop(bool boolean) {Stop = boolean;}

    void setLED1(bool boolean) {LED1 = boolean;}
    void setLED2(bool boolean) {LED2 = boolean;}
    void setLED3(bool boolean) {LED3 = boolean;}




private:
    CServer serverCOMP;
    std::vector<std::string> _cmds;

    // booleans
    bool Forward;
    bool Backward;
    bool Right;
    bool Left;
    bool Stop;

    bool LED1;
    bool LED2;
    bool LED3;


};



#endif // CCOMMUNICATION_H
