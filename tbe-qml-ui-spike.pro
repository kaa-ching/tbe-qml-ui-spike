TEMPLATE = app

QT += qml quick quickwidgets
QT += core gui widgets
CONFIG += c++11

SOURCES += main.cpp \
    AbstractObject.cpp \
    MainWindow.cpp \
    ViewItem.cpp \
    World.cpp \
    Position.cpp \
    ResolutionConversionSingleton.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

HEADERS += \
    AbstractObject.h \
    MainWindow.h \
    Popup.h \
    ViewItem.h \
    World.h \
    Position.h \
    ResolutionConversionSingleton.h

FORMS    += mainwindow.ui
