#ifndef LINECHART_H
#define LINECHART_H

#include "comportthread.h"
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <windows.h>
#include <QTimer>

class LineChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit LineChart(QQuickPaintedItem *parent = 0);
    void paint(QPainter *painter);

    Q_PROPERTY(QColor color READ color WRITE setColor)
    QColor color() const;
    void setColor(const QColor &color);

    Q_INVOKABLE bool startPort();
    Q_INVOKABLE void stopPort(){ifShow = false;}
    Q_INVOKABLE void restartPort(){ifShow = true;}

    // close work thread
    void closeEvent(QCloseEvent *event);

private slots:
    void onUpdate(){if(ifShow)update();}

private:
    bool ifShow;       // when we push the pause button we dont repaint the chart
    QColor m_color;
    int topDistance;   // distance to the top of the picture
    ComPortThread *comPortThread;
};

#endif // LINECHART_H
