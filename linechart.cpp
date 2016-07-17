/*********************************************************************************************/

// PAINT STRATEGY:
// The data will be received from the com port, so the chart will be update all the time
// we will update the chart at the same time as we get a packet of data from the port
// so the repaint process is done in the onTimer function.
// when we arrive at the max point we will clear the chart and repaint from the fisrt point

// UPDATE UI
// at the beginning, we update the ui in the onTimer of port, but this will delay the timer,
// so we build a new thread to receive the data from com port

// 2016.4.29   Author : Wenhao Ding                                                   All Rights Reserved
/*********************************************************************************************/

#include "linechart.h"
#include <QPainter>
#include <QDate>
#include <QDebug>
#include <stdlib.h>
#include <QThread>


#define WIDTH 1               // the distance between two points
#define ORIGINAL 280     // the x axis position

LineChart::LineChart(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    topDistance = 120;
    comPortThread = new ComPortThread;
    ifShow = true;

    // every time the port thread receives a data, emit a signal and GUI thread update the UI
    connect(comPortThread, SIGNAL(dataUpdated()), this, SLOT(onUpdate()));
}

// paint the chart every time the update called
void LineChart::paint(QPainter *painter)
{
    comPortThread->mutex.lock();
    int copyCurrentNumber = comPortThread->currentNumber;
    int *copyArray = new int[copyCurrentNumber];

    for(int i = 0;i < copyCurrentNumber;++i)
    {
        if(comPortThread->numberPoint[i] < 360)
            copyArray[i] = comPortThread->numberPoint[i];
        else
            copyArray[i] = 0;
    }

   comPortThread->mutex.unlock();

    painter->setRenderHint(QPainter::Antialiasing);   // smooth line

    int flag = -1;
    for(int i = 0;i < copyCurrentNumber;i++)
        if(flag < abs(copyArray[i]))
            flag = abs(copyArray[i]);

    painter->translate(0, ORIGINAL);     // put the origin position, the y distance is 530
    QPen penLine(Qt::white, 2);               // set the color and size of the line
    painter->setPen(penLine);

    // draw lines and points
    // the distance between points is defined as WIDTH
    for (int var = 0; var < copyCurrentNumber; ++var)
    {
        if(var == 0)  // the first point
            painter->drawLine(0,
                                            0,
                                            WIDTH,
                                            -copyArray[var]*(ORIGINAL-topDistance)/flag);
        else
            painter->drawLine((WIDTH + (var-1)*2*WIDTH),
                                             -copyArray[var-1]*(ORIGINAL-topDistance)/flag,
                                             2*WIDTH*var+WIDTH,
                                             -copyArray[var]*(ORIGINAL-topDistance)/flag);
    }

    // draw the ellipse
    for (int var = 0; var < copyCurrentNumber; ++var)
        painter->drawEllipse((WIDTH+var*2*WIDTH)-1,
                                            (-copyArray[var]*(ORIGINAL-topDistance)/flag)-1,
                                            2,
                                            2);

    QPen Vertical(Qt::white,1);
    painter->setPen(Vertical);

    // draw the verticle lines
    for (int var = 0; var < copyCurrentNumber; ++var)
        painter->drawLine((WIDTH+var*2*WIDTH),
                                        0,
                                        (WIDTH+var*2*WIDTH),
                                        -copyArray[var]*(ORIGINAL-topDistance)/flag+5);

    // paint the words on the picture
    for (int var = 0; var < copyCurrentNumber; ++var)
    {
        if(var % 10 == 0)
        {
            QFont isToday("white",10);
            painter->setFont(isToday);
            QString flagstr = "";
            flagstr = QString::number(copyArray[var]);
            if(copyArray[var] > 0)
                painter->drawText((WIDTH+var*2*WIDTH),-copyArray[var]*(ORIGINAL-topDistance)/flag-25, flagstr);
            else
                painter->drawText((WIDTH+var*2*WIDTH),-copyArray[var]*(ORIGINAL-topDistance)/flag+25,flagstr);
        }
    }

    // draw the shadow downside the line
    QColor insideBrushColor(255,255,255,25);
    QPen penpoints(insideBrushColor,0.15);
    painter->setPen(penpoints);
    painter->setBrush(insideBrushColor);
    QPointF *points = new QPointF[copyCurrentNumber];
    points[0] = QPointF(0.0, 0.0);
    for (int var = 1; var < copyCurrentNumber; ++var)
    {
            float x = (WIDTH+(var-1)*2*WIDTH);
            float y = (-copyArray[var-1]*(ORIGINAL-topDistance)/flag);
            points[var] = QPointF(x, y);
    }
    points[copyCurrentNumber-1]=QPointF(WIDTH+(copyCurrentNumber)*2*WIDTH, 0.0);
    painter->drawConvexPolygon(points, copyCurrentNumber);
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

bool LineChart::startPort()
{
    comPortThread->start();
    return comPortThread->opened;
}

void LineChart::closeEvent(QCloseEvent *event)
{
     comPortThread->stop();
     comPortThread->wait();
     event->accept();
 }
