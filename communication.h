#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "qextserialbase.h"
#include "win_qextserialport.h"
#include <qobject>

class Communication : public QObject
{
    Q_OBJECT
public:
    Communication();
     bool OpenPort();
     void ReceiveData();
     void sendData();
     void stop();

private:
    Win_QextSerialPort *com;

    char data[33];
    char receive[3];
    bool isOpened;
};

#endif // _COMMUNICATION_H
