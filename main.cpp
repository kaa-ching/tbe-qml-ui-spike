#include <QApplication>
#include "MainWindow.h"
#include "ResolutionConversionSingleton.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    ResolutionConversionSingleton::me();

    return app.exec();
}
