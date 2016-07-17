#include "comportthread.h"
#include <qdebug.h>
#include <iomanip>

#define MAX_NUMBER 600
#define RECEIVE_TIME_INTERVAL 10   // date receive time
#define MAX_MISSING      1000


ComPortThread::ComPortThread()
{
    com = new Win_QextSerialPort("COM7",QextSerialBase::EventDriven);
    stopped = false;
    currentNumber = 1;
    numberPoint = new int[MAX_NUMBER];
    for(int i = 0;i < MAX_NUMBER;++i)
        numberPoint[i] = 10;

    receive = new char[4];
}

// read data from the port
bool ComPortThread::readComPort()
{
    for(int i = 0;i < 4;++i)      //init data array
            receive[i] = 0x00;

    char* temp = new char;
    bool flag = false;
    int t;
    if(opened)
    {
            while(!flag && (t =  com->read(temp, 1)))
            {
                if(temp[0] == 0x0a)
                {
                    flag = true;
                    break;
                }
            }
            com->read(receive, 4);

           if (!(receive[2] == 0x0d && receive[3] == 0x0a))
               return false;

           // char --- 1 byte  short int --- 2 bytes  int --- 4 bytes
           WORD differenceMotor = 0x00;
           int showNumber = 0;
           differenceMotor = receive[1] & 0x00ff;  // clear high 8 bits
           differenceMotor = (receive[0] << 8) | differenceMotor;
            if(differenceMotor >> 15 == 0x0001)    // negative number
            {
                differenceMotor = ~differenceMotor + 0x0001;
                showNumber = -differenceMotor;
            }
            else
                 showNumber = differenceMotor;

           //////// warning ////////
           // when we print the number, there will be a long time delay
           //qDebug() << hex <<differenceMotor << endl;

           // lock this varaiable to avoid other thread's visiting
           mutex.lock();
           if(currentNumber == 1)
                numberPoint[0] = 1;
           else
                numberPoint[currentNumber-1] = showNumber;
           mutex.unlock();
           // lock finished
           //qDebug() << numberPoint[currentNumber-1] << endl;
           return true;
    }
    return false;
}

// serialport operating
bool ComPortThread::openComPort()
{
      opened = com->open(QIODevice::ReadWrite);// double port
        if(opened)                               // check if open successfully
        {
            com->setBaudRate(BAUD115200);          // BAUD 115200
            com->setDataBits(DATA_8);                     // data bits 8
            com->setParity(PAR_NONE);                   // check bit  no
            com->setStopBits(STOP_1);                    // stop bit  1
            com->setFlowControl(FLOW_OFF);        // data stream
            com->setTimeout(500);                             // delay 500ms
            return opened;
        }
        else
            return opened;
}

// run a new thread
void ComPortThread::run()
{
    opened = openComPort();
    while(!stopped)
    {
        // only receive successfully, we can repaint the chart
        int flag = readComPort();

        // repaint the chart and update the current number
        if(flag)
        {
            currentNumber++;
            if(currentNumber == MAX_NUMBER)
                currentNumber = 1;
            emit dataUpdated();
        }

        // this parameter will decide the speed of drawing
        msleep(5);
    }
}
