#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <thread>

using namespace cv;
using namespace std;
#include "CServer.h"
#include "CControl.h"

////////////////////////////////////////////////////////////////
// Demo client server communication
////////////////////////////////////////////////////////////////

#include <chrono>
void serverthread(CServer* server)
{
  // Start server
  server->start(4618);
}

void do_clientserver()
{
  char inputchar = 0;
  std::vector<std::string> cmds;

  cv::VideoCapture vid;
  CServer server;

  // Start server thread
std::thread t(&serverthread, &server);
t.detach();

    // open camera
    vid.open(0, cv::CAP_V4L2);

    // camera resoution get
    double width = vid.get(cv::CAP_PROP_FRAME_WIDTH); // Get the width
    double height = vid.get(cv::CAP_PROP_FRAME_HEIGHT); // Get the height
    cout << "Width : " << width << " Height : " << height << endl;

while (inputchar != 'q')
{
   inputchar = cv::waitKey(100);

   server.get_cmd(cmds);
   if (cmds.size() > 0)
   {
      // Process different commands received by the server
      for (int i = 0; i < cmds.size(); i++)
      {
         if (cmds.at(i) == "im")
         {
            std::cout << "\nServer Rx: " << cmds.at(i);

            std::string reply = "Hi there from Server";
            server.send_string(reply);
         }
         else
         {
            std::cout << "\nServer Rx: " << cmds.at(i);

            std::string reply = "Got some other message";
            server.send_string(reply);
         }
      }
   }

   // Update server image with the latest camera image
   if (vid.isOpened() == true)
   {
      cv::Mat frame;
      vid >> frame;
      if (frame.empty() == false)
      {
         imshow("Server Image", frame);
         cv::waitKey(1);
         server.set_txim(frame);
      }
   }
};

server.stop();

std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

#include "CCommunication.h"
////////////////////////////////////////////////////////////////
// Lab 1
////////////////////////////////////////////////////////////////
void lab1()
{
    CCommunication comm;
    do
    {
        comm.check();
    }while(1);
}

////////////////////////////////////////////////////////////////
// Lab 2
////////////////////////////////////////////////////////////////
#include "CCoolCar.h"
void lab2()
{
    CCoolCar coolcar(1);
    coolcar.run();
}

////////////////////////////////////////////////////////////////
// Lab 3
////////////////////////////////////////////////////////////////
void lab3()
{
}



////////////////////////////////////////////////////////////////
// Lab 4
////////////////////////////////////////////////////////////////
void lab4()
{
}

////////////////////////////////////////////////////////////////
// Lab 5
////////////////////////////////////////////////////////////////
void lab5()
{
}

////////////////////////////////////////////////////////////////
// Lab 6
////////////////////////////////////////////////////////////////
void lab6()
{
}

////////////////////////////////////////////////////////////////
// Lab 7
////////////////////////////////////////////////////////////////
#include "CControl.h"
void lab7()
{
    CControl controller;
    while(controller.print_menu());
}
////////////////////////////////////////////////////////////////
// Lab 8
////////////////////////////////////////////////////////////////

void lab8()
{

}
////////////////////////////////////////////////////////////////
// Lab 9
////////////////////////////////////////////////////////////////
void lab9()
{

}

void print_menu()
{
    system("clear");
    std::cout << "\n***********************************";
    std::cout << "\n* ELEX4699 CoolCar Project";
    std::cout << "\n***********************************";
    std::cout << "\n(1) Experiment 1 - Testing COMM";
    std::cout << "\n(2) Experiment 2 - Automotive Manual";
    std::cout << "\n(3) Experiment 3 - Automotive Guidance Test";
    std::cout << "\n(4) Lab 4 - Etch-A-Sketch";
    std::cout << "\n(5) Lab 5 - Pong";
    std::cout << "\n(6) Lab 6 - Classic Arcade Game";
    std::cout << "\n(7) Lab 7 - CControl Test";
    std::cout << "\n(8) Lab 8 - Sorting";
    std::cout << "\n(13) Test client/server communication";
    std::cout << "\n(0) Exit";
    std::cout << "\nCMD> ";
}

int main(int argc, char* argv[])
{
    int cmd = -1;
    do
    {
        print_menu();
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            lab1();
            break;
        }
        case 2:
        {
            lab2();
            break;
        }
        case 3:
        {
            lab3();
            break;
        }
        case 4:
        {
            lab4();
            break;
        }
        case 5:
        {
            lab5();
            break;
        }
        case 6:
        {
            lab6();
            break;
        }
        case 7:
        {
            lab7();
            break;
        }
        case 8:
        {
            lab8();
            break;
        }
        case 13:
        {
            do_clientserver();
            break;
        }
        }
    }
    while (cmd != 0);
}
