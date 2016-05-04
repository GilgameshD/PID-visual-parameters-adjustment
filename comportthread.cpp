#include "comportthread.h"
#include <qdebug.h>

#define MAX_NUMBER 90
#define RECEIVE_TIME_INTERVAL 10   // date receive time
#define MAX_MISSING      1000

ComPortThread::ComPortThread()
{
    stopped = false;
    currentNumber = 1;
    numberPoint = new int[MAX_NUMBER];
    for(int i = 0;i < MAX_NUMBER;++i)
        numberPoint[i] = 2;
}

// read data from the port
bool ComPortThread::readComPort()
{
    DWORD dwRead;
    char m_pDataBuf[1000]; // receive buffer
    DWORD temp;
    COMSTAT comstat;
    bool flag = false;

    // Get Serial states
    ClearCommError(serialPort, &temp, &comstat);

    // New bytes pending read or not
    if (comstat.cbInQue > 0)
    {
        flag = ReadFile(serialPort, m_pDataBuf, comstat.cbInQue, &dwRead, NULL);
        m_pDataBuf[dwRead] = 0;

        qDebug() << m_pDataBuf;
        int tmp = atoi(m_pDataBuf);
        if(abs(tmp) < MAX_MISSING)
            numberPoint[currentNumber-1] = tmp;
        else
            return false;
    }
    return flag;
}

// serialport operating
bool ComPortThread::openComPort()
{
    wchar_t auxstr[10]  = {'C', 'O', 'M', '8'};
    DCB dcb;
    serialPort = CreateFile(auxstr, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if(!GetCommState(serialPort, &dcb))
        return false;

    // Serial port configuration
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;

    if (!SetCommState(serialPort, &dcb))
        return false;
    return true;
}

void ComPortThread::run()
{
    opened = openComPort();
    while(!stopped)
    {
        int flag = readComPort();

        // repaint the chart and update the current number
        if(flag)
        {
            currentNumber++;
            emit dataUpdated();
        }
        if(currentNumber == MAX_NUMBER)
            currentNumber = 1;
        msleep(20);
    }
}







