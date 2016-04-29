#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "qextserialbase.h"
#include "win_qextserialport.h"
#include <qobject>
#include <qstring.h>

class Communication : public QObject
{
    Q_OBJECT
public:
    Communication();
    Q_INVOKABLE bool openPort();
    Q_INVOKABLE void receiveData();
    Q_INVOKABLE void sendData();
    Q_INVOKABLE void stop();

private:
    Win_QextSerialPort *com;

    // the data received from the port and bind with qml to be shown
    QString dataToBeShown;

    char data[33];
    char receive[3];
    bool isOpened;
};

#endif // _COMMUNICATION_H
