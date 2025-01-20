#include "CCommunication.h"

// set to true to display console text
#define DISPLAY true

void CCommunication::check()
{
    serverCOMP.get_cmd(_cmds);


    if (_cmds.size() > 0)
    {
        // Process different commands received by the server
        for (int i = 0; i < _cmds.size(); i++)
        {
            if (_cmds.at(i) == "im")
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);

            }

            // LED 1
            else if (_cmds.at(i) == "S 0 01 \n") // turn LED1 ON
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED1 = true;
                serverCOMP.send_string("LED1 ON");
            }
            else if (_cmds.at(i) == "S 0 00 \n") // turn LED1 OFF
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED1 = false;
                serverCOMP.send_string("LED1 OFF");
            }

            // LED 2
            else if (_cmds.at(i) == "S 0 11 \n") // turn LED1 ON
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED2 = true;
                serverCOMP.send_string("LED2 ON");
            }
            else if (_cmds.at(i) == "S 0 10 \n") // turn LED1 OFF
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED2 = false;
                serverCOMP.send_string("LED2 OFF");
            }

            // LED 3
            else if (_cmds.at(i) == "S 0 21 \n") // turn LED3 ON
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED3 = true;
                serverCOMP.send_string("LED3 ON");
            }
            else if (_cmds.at(i) == "S 0 20 \n") // turn LED3 OFF
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                LED3 = false;
                serverCOMP.send_string("LED3 OFF");
            }


            // DRIVING FORWARD
            else if (_cmds.at(i) == "S 3 01 \n") // MOTOR MOVE FORWARD
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                Forward = true;
                serverCOMP.send_string("MOVING FORWARD");
            }

            // DRIVING RIGHT
            else if (_cmds.at(i) == "S 3 11 \n") // MOTOR MOVE FORWARD
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                Right = true;
                serverCOMP.send_string("MOVING RIGHT");
            }

            // DRIVING LEFT
            else if (_cmds.at(i) == "S 3 21 \n") // MOTOR MOVE FORWARD
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                Left = true;
                serverCOMP.send_string("MOVING LEFT");
            }

            // DRIVING BACKWARDS
            else if (_cmds.at(i) == "S 3 31 \n") // MOTOR MOVE FORWARD
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                Backward = true;
                serverCOMP.send_string("MOVING BACKWARD");
            }

            else if (_cmds.at(i) == "S 3 00 \n") // MOTOR STOP
            {
                std::cout << "\nServer Rx: " << _cmds.at(i);
                Forward = false;
                Left = false;
                Right = false;
                Backward = false;
                serverCOMP.send_string("STOPPED");
            }



        }

    }
}

void CCommunication::server_start(CServer* server, int port)
{
    server->start(port);
}

void CCommunication::S1() // PORT 2374 COMP
{
    server_start(&serverCOMP, 2374);
}

CCommunication::CCommunication()
{
    // Start serverCOMP
    std::thread s1(&CCommunication::S1, this);
    s1.detach();
}

CCommunication::~CCommunication()
{
    //dtor
}
