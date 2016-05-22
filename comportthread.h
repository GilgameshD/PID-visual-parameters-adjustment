#ifndef COMPORTTHREAD
#define COMPORTTHREAD

#include <qthread.h>
#include <qtimer.h>
#include "qextserialbase.h"
#include "win_qextserialport.h"


class ComPortThread : public QThread
{
    Q_OBJECT
public:
    ComPortThread();
    void stop() {stopped = true;}
    bool openComPort();
    bool readComPort();

    int *numberPoint;
    int currentNumber;
    bool opened;   // record if the port is opened
    QMutex mutex;

    // thread opening
    void run();

signals:
    void dataUpdated();

private:
    volatile bool stopped;
    Win_QextSerialPort *com;
    char *receive;
};

#endif // COMPORTTHREAD

