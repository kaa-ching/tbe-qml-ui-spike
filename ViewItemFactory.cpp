#include "ViewItemFactory.h"

#include <QQuickItem>
#include <QQmlComponent>
#include "QDebug"

ViewItemFactory::ViewItemFactory(QQuickWidget *parent)
    : QObject(parent),
      theRQWPtr(parent)
{
    // nothing to do...
}

ViewItem *ViewItemFactory::createViewItem(AbstractObject *anAOPtr)
{
    // Create a ViewObject with name [hex representation of anAOPtr].
    QString myMsg; myMsg.sprintf("%p", anAOPtr);
    QVariant myReturnedValue;
    QMetaObject::invokeMethod(theRQWPtr->rootObject(), "createViewObject",
                              Q_RETURN_ARG(QVariant, myReturnedValue),
                              Q_ARG(QVariant, myMsg));
    assert(myReturnedValue.toBool());

    // Once we get here, there should now be a ViewObject with the name.
    QQuickItem *myVOPtr = theRQWPtr->rootObject()->findChild<QQuickItem*>(myMsg);
    assert (myVOPtr!=nullptr);
    QList<QQuickItem*> myChilds = myVOPtr->childItems();
    for (auto I : myChilds) {
        if (I->objectName() == "theVI")
            return qobject_cast<ViewItem*>(I);
    }
    return nullptr;
}
