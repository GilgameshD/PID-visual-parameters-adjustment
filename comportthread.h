#ifndef COMPORTTHREAD
#define COMPORTTHREAD

#include <qthread.h>
#include <qtimer.h>
#include "windows.h"

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

    // thread opening
    void run();

signals:
    void dataUpdated();

private:
    volatile bool stopped;
    HANDLE serialPort;  // Serial port HANDLE
};

#endif // COMPORTTHREAD

