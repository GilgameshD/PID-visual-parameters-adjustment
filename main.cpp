#include "linechart.h"
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlContext>

int main(int argc, char *argv[])
{
     QGuiApplication app(argc, argv);

     // build a instance of the class LineChart and load the qml
    qmlRegisterType<LineChart>("LineCharts", 1, 0, "LineChart");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    // hind the frame of the window and register the mainwindow to qml to drag the window
    //view.setFlags(Qt::Window | Qt::FramelessWindowHint);
    view.rootContext()->setContextProperty("mainwindow",&view);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    return app.exec();
}
