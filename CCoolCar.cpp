#include "CCoolCar.h"

void CCoolCar::Automotive_Software()
{
    std::cout << "in loop";
    do
    {
        // 1. Check
        // 2. Act
        // 3. Loop

        // CHECK
        _commPI.check();

        // ACT
        if (_commPI.getLED1() == true)
            gpioWrite(LED1, 1);
        else
            gpioWrite(LED1, 0);

        // MOTOR
        if (_commPI.getForward() == true)
            _motorPI.mov_Forward(100);

        else if (_commPI.getBackward() == true)
            _motorPI.mov_Backward(100);

        else if (_commPI.getRight() == true)
            _motorPI.mov_Right(100);

        else if (_commPI.getLeft() == true)
            _motorPI.mov_Left(100);

        else
            _motorPI.mov_Stop();


    }
    while (_loop == true);
}

void CCoolCar::initGPIO()
{
    // HAS PIGPIO LIBRARY BEEN INITIALIZED?
    if (gpioInitialise() < 0)
    {
        std::cout << "\nCCC(): PIGPIO Initialization Failure";
    }
    else
    {
        std::cout << "\nCCC(): PIGPIO has been initialized.";
    }

    // SPI CONNECTION (10-bit ADC Response)
    handler_SPI = spiOpen(0, 200000, 3); // Mode 0, 200kHz, 3 bytes

    if (handler_SPI < 0)
    {
        std::cout << "\nSPI Connection Failed";
    }
    else
    {
        std::cout << "\nSPI Has Been Connected";
    }
}

void CCoolCar::destroyGPIO()
{
    std::cout << "DESTROYED CCONTROL\n";
    // Resets the used DMA channels, releases memory,
    // and terminates any running threads.
    gpioTerminate();

    if (handler_SPI > 0)
        spiClose(handler_SPI);
}

CCoolCar::CCoolCar(int version)
{
    // Initialize Variables
    _loop = true;


    // Initiate GPIOS //
    initGPIO();

    // MOTOR
    gpioSetMode(AI1, PI_OUTPUT);
    gpioSetMode(AI2, PI_OUTPUT);
    gpioSetMode(BI1, PI_OUTPUT);
    gpioSetMode(BI2, PI_OUTPUT);
    gpioSetMode(STBY, PI_OUTPUT);
    gpioSetMode(PWMA, PI_OUTPUT);
    gpioSetMode(PWMB, PI_OUTPUT);

    // LEDS
    gpioSetMode(LED1, PI_OUTPUT);
    gpioSetMode(LED2, PI_OUTPUT);
    gpioSetMode(LED3, PI_OUTPUT);


    // Initialize Threading
    _engine = std::thread(&CCoolCar::Automotive_Software, this);
    _engine.detach();
}

// Called when you quit the program
CCoolCar::~CCoolCar()
{
    _loop = false;
    if (_engine.joinable())
    {
        _engine.join();
    }
    /*
    if (_graphics.joinable())
    {
        _graphics.join();
    }
    */

    //cv::destroyAllWindows();
    //_camera.release();
    destroyGPIO();
}


void CCoolCar::run()
{
    using namespace cv;
    using namespace std;

    int key;
    bool run = true;

    do
    {
        // Initialize ncurses library
        initscr();
        // Don't wait for Enter key
        cbreak();
        // Don't display characters
        noecho();
        // Enable function keys
        keypad(stdscr, TRUE);
        // Don't block on read
        nodelay(stdscr, TRUE);

        int ch = getch();

        // End ncurses mode (like terminate)
        endwin();

        if (ch == ERR)
        {
            // No key was pressed
            key = -1;
        }
        else
        {
            // A key was pressed
            key = ch;
        }

        if (key == 'q' || key == 'Q')
        {
            run = false; // cool library
        } // cool library
    }
    while (run);
}
