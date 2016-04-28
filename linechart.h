#ifndef LINECHART_H
#define LINECHART_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

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

signals:
    void chartCleared();

private:
    QColor m_color;
    int monthCount;
    int nameWidth;
    int monthNow;
    int dayNow;
    int topDistance;   // distance to the top of the picture

};

#endif // LINECHART_H
