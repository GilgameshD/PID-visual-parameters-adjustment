#ifndef LINECHART_H
#define LINECHART_H

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

    /***************************************************************/
    Q_PROPERTY(QColor color READ color WRITE setColor)
    QColor color() const;
    void setColor(const QColor &color);
    /**************************************************************/

    Q_INVOKABLE void clearChart(); // join the qml

    /**************************************************************/
    Q_INVOKABLE bool openComPort();
    Q_INVOKABLE void pausePort();
    Q_INVOKABLE void restartPort();

    bool readComPort();
    /**************************************************************/
signals:
    void chartCleared();

private slots:
    void onPortReceiveTimer();

private:
    HANDLE serialPort;  // Serial port HANDLE
    QTimer *portReceiveTimer;

    QColor m_color;
    int topDistance;   // distance to the top of the picture
};

#endif // LINECHART_H
