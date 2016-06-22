#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "AbstractObject.h"
#include "ResolutionConversionSingleton.h"
#include "ViewItem.h"
#include "World.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ViewItem>("TBEView", 1, 0, "ViewItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // load our objects into the view
    World myWorld(4,6);
//    ResolutionConversionSingleton myRCS(engine);

    AbstractObject myObject1("BowlingPin", Position(2, 3, 0.2), 0.12, 0.34);
    myWorld.addObject(&myObject1);
    AbstractObject myObject2("used_wood_bar", Position(2, 2.5, 0.0), 1.0, 0.1);
    myWorld.addObject(&myObject2);
    AbstractObject myObject3("used_wood_bar", Position(1, 2.0, 0.0), 2.0, 0.5);
    myWorld.addObject(&myObject3);

    return app.exec();
}
