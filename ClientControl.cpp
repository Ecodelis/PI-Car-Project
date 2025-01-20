

#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <regex>
#include <conio.h>

#include "Client.h"

std::string server_ip_vehicle = "192.168.137.164";
std::string server_ip_arena = "192.168.0.100";

CClient client_car;
CClient client_cam; // for live camera feed

float timeout_start;
float timer1;
int server_COMP = 4618; // use even numbers
int server_CAM = 4616; // for cam
int server_ARENA = 5016; // Port for arena

// awaiting information from server
void send_command(CClient& client, int server_port, std::string cmd)
	{
	std::string str;

	// transmit string
	client.tx_str(cmd);
	//std::cout << "\nClient Tx: " << cmd;

	if (cmd == "im")
		{
		cv::Mat im;
		if (client.rx_im(im) == true)
			{
			timeout_start = cv::getTickCount();
			if (im.empty() == false)
				{
				//std::cout << "\nClient Rx: Image received";
				cv::Size targetSize(640, 480);
				cv::resize(im, im, targetSize);
				
				cv::imshow("rx", im);
				cv::waitKey(1);
				}
			}
		else
			{
			if ((cv::getTickCount() - timeout_start) / cv::getTickFrequency() > 1000)
				{
				// No response, disconnect and reconnect
				timeout_start = cv::getTickCount();
				client.close_socket();
				client.connect_socket(server_ip_vehicle, server_port);
				}
			}
		}
	else
		{
		if (client.rx_str(str) == true)
			{
			timeout_start = cv::getTickCount();
			std::cout << "\nClient Rx: " << str;
			}
		else
			{
			if ((cv::getTickCount() - timeout_start) / cv::getTickFrequency() > 1000)
				{
				// No response, disconnect and reconnect
				timeout_start = cv::getTickCount();
				client.close_socket();
				client.connect_socket(server_ip_vehicle, server_port);
				}
			}
		}
	}

bool checkUserInput(std::string input, int checkType)
	{
	using namespace std;

	// Checks for proper menu input
	regex menu("^[12345qQ+]");

	// Checks for number input for On/Off menus
	regex switchMenu("^[qQ0-1]");

	// Checks for LED input
	regex ledMenu("^[qQ1-3]");

	regex type[] = { menu, switchMenu, ledMenu };

	if (regex_match(input, type[checkType]))
		{
		return false;
		}
	else
		{
		cout << "Invalid input!\n";
		return true;
		}
	}

int keyStrokeCheck()
	{
	// Check for keystroke
	if (_kbhit())
		{
		return _getch();
		}
	else
		{
		return -1; // return -1 if false
		}
	}

void menu_Main(int& menu_num, int& cmd)
	{
	using namespace std;
	string userInput;

	cout
		<< "\n****************************************" << endl
		<< "Car Debugging System, by Marcus Fu" << endl
		<< "****************************************" << endl
		<< "(1) Start Driving" << endl
		<< "(2) Test Connection LED" << endl
		<< "(3) Permanently Enable PICAM" << endl
		<< "(4) Get PICAM Resolution" << endl
		<< "(Q) Quit" << endl;

	do
		{
		cin >> userInput;
		cin.ignore();
		} while (checkUserInput(userInput, 0));

		// Main menu logic
		switch (userInput.at(0))
			{
			case '1':
				menu_num = 1; break;

			case '2':
				menu_num = 2;  break;
			case '3':
				menu_num = 3; break;
			case 'Q':
			case 'q':
				menu_num = -1;
			}
	}


bool LED1 = false;
bool LED2 = false;
bool LED3 = false;

void menu_LEDTEST(int& menu_num, int& cmd)
	{
	using namespace std;
	string userInput;

	cout
		<< "\n****************************************" << endl
		<< "LED1 TEST (Toggle)" << endl
		<< "****************************************" << endl
		<< "(1) LED1" << endl
		<< "(2) LED2" << endl
		<< "(3) LED3" << endl
		<< "(Q) Quit" << endl;


	do
		{
		cin >> userInput;
		cin.ignore();
		} while (checkUserInput(userInput, 2));

		// Main menu logic
		switch (userInput[0])
			{
			case '1':
				if (LED1 == false)
				{
					LED1 = true;
					send_command(client_car, server_COMP, "S 0 01 \n");
				}
				else if (LED1 == true)
				{
					LED1 = false;
					send_command(client_car, server_COMP, "S 0 00 \n");
				}
				break;

			case '2':
				if (LED2 == false)
					{
					LED2 = true;
					send_command(client_car, server_COMP, "S 0 11 \n");
					}
				else if (LED2 == true)
					{
					LED2 = false;
					send_command(client_car, server_COMP, "S 0 10 \n");
					}
				break;
			case '3':
				if (LED3 == false)
					{
					LED3 = true;
					send_command(client_car, server_COMP, "S 0 21 \n");
					}
				else if (LED3 == true)
					{
					LED3 = false;
					send_command(client_car, server_COMP, "S 0 20 \n");
					}
				break;
			case 'Q':
			case 'q':
				menu_num = 0;
			}
	}

void menu_DRIVE(int& menu_num, int& cmd)
	{
	using namespace std;
	char input;
	bool forward, backward, left, right;
	forward = false;
	backward = false;
	left = false;
	right = false;

	cout
		<< "\n****************************************" << endl
		<< "Manual Drive" << endl
		<< "****************************************" << endl
		<< "(W) FORWARD" << endl
		<< "(A) LEFT" << endl
		<< "(S) RIGHT" << endl
		<< "(D) BACKWARD" << endl
		<< "(Q) Quit" << endl;

	do
	{


		// Check for keystroke
		if (_kbhit())
			{
			input = _getch();
			}
		else
			{
			input = -1; // return -1 if false
			}

	// Main menu logic
		switch (input)
		{
			case 'w':
			{
			forward = true;
			backward = false;
			left = false;
			right = false;
			break;
			}
		case 'd':
			{
			forward = false;
			backward = false;
			left = false;
			right = true;
			break;
			}
		case 'a':
			{
			forward = false;
			backward = false;
			left = true;
			right = false;
			break;
			}
		case 's':
			{
			forward = false;
			backward = true;
			left = false;
			right = false;
			break;
			}
		case 'e':
			{
			forward = false;
			backward = false;
			left = false;
			right = false;
			break;
			}

		}

		if (forward == true)
		{
			send_command(client_car, server_COMP, "S 3 01 \n"); std::cout << "forwards"; // forward
		}
		else if (backward == true)
		{
			send_command(client_car, server_COMP, "S 3 31 \n"); std::cout << "backwards"; // backward
		}
		else if (left == true)
		{
			send_command(client_car, server_COMP, "S 3 11 \n"); std::cout << "right";// left
		}
		else if (right == true)
		{
			send_command(client_car, server_COMP, "S 3 21 \n"); std::cout << "left"; // right
		}
		else
			send_command(client_car, server_COMP, "S 3 00 \n"); std::cout << "none";

		std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Sleep for 50 milliseconds
	} while (toupper(input) != 'Q');

	menu_num = 0;
}

void cameralive(CClient& client)
	{

	do
		{
		send_command(client, server_CAM, "im");
		Sleep(33);

		} while (1);
	}


bool is_PICAM_enabled = false;

int main(int argc, char* argv[])
	{
	int cmd = -1;
	int menu_num = 0;

	timeout_start = cv::getTickCount();
	client_car.connect_socket(server_ip_vehicle, server_COMP);

	Sleep(1000);

	timeout_start = cv::getTickCount();
	client_cam.connect_socket(server_ip_vehicle, server_CAM);

	std::thread t1(cameralive, client_cam);
	t1.detach();

	do
		{
		bool showStream = false;
		//system("CLS"); // clears console

		switch (menu_num)
		{
			case 0:
				menu_Main(menu_num, cmd); break;
			case 1:
				menu_DRIVE(menu_num, cmd); break;
			case 2:
				menu_LEDTEST(menu_num, cmd); break;
			case 3:
			{
				if (is_PICAM_enabled == false)
				{
				//std::thread t1(cameralive, client_cam);
				//t1.detach();

				is_PICAM_enabled = true;
				menu_num = 0;
				}
				else
				{
					std::cout << "\nPICAM is already enabled!";
					menu_num = 0;
				}
			}
			case 4:
			{
				send_command(client_cam, server_CAM, "S 0 0 \n"); break;
			}
		}


		if (cmd > 0)
			{
			switch (cmd)
				{
				case 1: send_command(client_car, server_COMP, "im"); break;

				case 2: send_command(client_car, server_COMP, "S 0 0 \n"); break; //system off
				case 3: send_command(client_car, server_COMP, "S 0 1 \n"); break; //system on

				case 4: send_command(client_car, server_COMP, "S 1 0 \n"); break; // send blue
				case 5: send_command(client_car, server_COMP, "S 1 1 \n"); break; // send green
				case 6: send_command(client_car, server_COMP, "S 1 2 \n"); break; // send yellow
				case 7: send_command(client_car, server_COMP, "S 1 3 \n"); break; // send pink
				case 8: send_command(client_car, server_COMP, "G 0 0 \n"); send_command(client_car, server_COMP, "G 0 1 \n"); send_command(client_car, server_COMP, "G 0 2 \n"); send_command(client_car, server_COMP, "G 0 3 \n"); break;

				}
			cmd = -1;

			Sleep(10);
			}

		} while (menu_num != -1);
	}
