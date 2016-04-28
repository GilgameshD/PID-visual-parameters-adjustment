TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    linechart.cpp \
    qextserialbase.cpp \
    qextserialport.cpp \
    win_qextserialport.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    linechart.h \
    qextserialbase.h \
    qextserialport.h \
    win_qextserialport.h

