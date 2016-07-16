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
    ViewItem* myVIPtr = ViewItem::findVIinVO(myVOPtr);
    assert (myVIPtr!=nullptr);

    // Let's tell the ViewItem who's his friend, they'll together make sure
    // the item gets displayed correctly.
    myVIPtr->setAbstractObjectPtr(anAOPtr);
    return myVIPtr;
}
