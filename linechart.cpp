#include "linechart.h"
#include <QPainter>
#include <QDate>
#include <QDebug>

/*********************************************************************************************/

// PAINT STRATEGY:
// The data will be received from the com port, so the chart will be update all the time
// we will update the chart at the same time as we get a packet of data from the port
// so the repaint process is done in the onTimer function.
// when we arrive at the max point we will clear the chart and repaint from the fisrt point

// 2016.4.29   Author : Wenhao Ding                                                   All rights Reserved
/*********************************************************************************************/


#define WIDTH 8               // the distance between two points
#define ORIGINAL 300     // the x axis position
#define DATA_COUNT 37
#define receiveTime 600   // date receive time

//  record the data to be shown
int traffic[37] = {700,-300,600,622,644,-800,723,777,500,800,-766,728,234,-245,222,
                         678,443,778,-235,-900,923,-618,-845,98,128,300, 0, 0, 0, 100,100, 250,
                         520 ,-510, 950, 840, 200};

LineChart::LineChart(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    topDistance =120;
    portReceiveTimer = new QTimer;
    portReceiveTimer->setInterval(receiveTime);

    connect(portReceiveTimer, SIGNAL(timeout()), this, SLOT(onPortReceiveTimer()));
}

void LineChart::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);   // smooth line

    int flag = 0;
    for(int i = 0;i < DATA_COUNT;i++)
        if(flag < traffic[i])
            flag = traffic[i];

    painter->translate(0, ORIGINAL);     // put the origin position, the y distance is 530
    QPen penLine(Qt::white, 3);               // set the color and size of the line
    painter->setPen(penLine);

    // draw lines and points
    // the distance between points is defined as WIDTH
    for (int var = 0; var < DATA_COUNT; ++var)
    {
        if(var == 0)  // the first point
            painter->drawLine(0,
                                            0,
                                            WIDTH,
                                            -traffic[var]*(ORIGINAL-topDistance)/flag);
        else
            painter->drawLine((WIDTH + (var-1)*2*WIDTH),
                                             -traffic[var-1]*(ORIGINAL-topDistance)/flag,
                                             2*WIDTH*var+WIDTH,
                                             -traffic[var]*(ORIGINAL-topDistance)/flag);
    }

    // draw the ellipse
    for (int var = 0; var < DATA_COUNT; ++var)
        painter->drawEllipse((WIDTH+var*2*WIDTH)-2, (-traffic[var]*(ORIGINAL-topDistance)/flag)-2, 4, 4);//-5

    QPen Vertical(Qt::white,1);
    painter->setPen(Vertical);

    // draw the verticle lines
    for (int var = 0; var < DATA_COUNT; ++var)
        painter->drawLine((WIDTH+var*2*WIDTH), 0, (WIDTH+var*2*WIDTH),-traffic[var]*(ORIGINAL-topDistance)/flag+5);

    // paint the words on the picture
    /**********************************************************************************************/
    for (int var = 0; var < DATA_COUNT; ++var)
    {
        QFont isToday("white",10);
        painter->setFont(isToday);
        QString flagstr = "";
        flagstr = QString::number(traffic[var]);
        painter->drawText((WIDTH+var*2*WIDTH-35),-traffic[var]*(ORIGINAL-topDistance)/flag-25,flagstr);
    }
    /******************************************************************************************************/

    // draw the shadow downside the line
    /******************************************************************************************************/
    QColor insideBrushColor(255,255,255,25);
    QPen penpoints(insideBrushColor,0.15);
    painter->setPen(penpoints);
    painter->setBrush(insideBrushColor);
    QPointF points[DATA_COUNT];
    points[0] = QPointF(0.0, 0.0);
    for (int var = 1; var < DATA_COUNT; ++var)
    {
            float x = (WIDTH+(var-1)*2*WIDTH);
            float y = (-traffic[var-1]*(ORIGINAL-topDistance)/flag);
            points[var] = QPointF(x, y);
    }
    points[DATA_COUNT-1]=QPointF(WIDTH+(DATA_COUNT)*2*WIDTH, 0.0);
    painter->drawConvexPolygon(points, DATA_COUNT);
    /******************************************************************************************************/
}

void LineChart::clearChart()
{
    qDebug() << "========================================";
    setColor(QColor(Qt::transparent));
    update();   // update the picture
    emit chartCleared();
}

// return the color
QColor LineChart::color() const
{
    return m_color;
}

// set the color
void LineChart::setColor(const QColor &color)
{
    m_color = color;
}

// read data from the port
bool LineChart::readComPort()
{
    DWORD dwRead;
    char m_pDataBuf[1000];
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
        qDebug() << m_pDataBuf << endl;
    }
    return flag;
}

// serialport operating
bool LineChart::openComPort()
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

    // start the timer and receive the data
    portReceiveTimer->start();
    return true;
}

void LineChart::onPortReceiveTimer()
{
    readComPort();
}

void LineChart::pausePort()
{
    portReceiveTimer->stop();
}

void LineChart::restartPort()
{
    portReceiveTimer->start();
}
