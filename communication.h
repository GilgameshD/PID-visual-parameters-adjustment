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

      // the data received from the port and bind with qml to be shown
    Q_INVOKABLE QString returnData();

private:
    Win_QextSerialPort *com;
    int dataLength;  // the length of the data sended
    char *data;
    char receive[3];
    bool isOpened;
};

#endif // _COMMUNICATION_H
