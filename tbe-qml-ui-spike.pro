TEMPLATE = app

QT += qml quick quickwidgets
QT += core gui widgets
CONFIG += c++11

SOURCES += main.cpp \
    AbstractObject.cpp \
    MainWindow.cpp \
    Position.cpp \
    ResizingQuickWidget.cpp \
    ResolutionConversionSingleton.cpp \
    ViewItem.cpp \
    ViewItemFactory.cpp \
    World.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

HEADERS += \
    AbstractObject.h \
    MainWindow.h \
    Popup.h \
    Position.h \
    ResizingQuickWidget.h \
    ResolutionConversionSingleton.h \
    ViewItem.h \
    ViewItemFactory.h \
    World.h

FORMS    += MainWindow.ui
