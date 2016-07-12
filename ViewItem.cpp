#include "AbstractObject.h"
#include "ViewItem.h"

ViewItem::ViewItem(QQuickItem *aParentPtr)
                       : QQuickItem(aParentPtr),
                         theAOPtr(nullptr)
{
    // Nothing to do here...
}


void
ViewItem::adjustObjectDrawingFromAO()
{
    assert(theAOPtr!=nullptr);

    // convert width and height from SI to pixels and set them
    QSize mySize = Vector(theAOPtr->theWidth, theAOPtr->theHeight).toQSize();
    parentItem()->setWidth(mySize.width());
    parentItem()->setHeight(mySize.height());

    // convert center position from SI to pixels and set the top-left position
    parentItem()->setRotation(theAOPtr->thePos.angleInDegrees());
    QPointF myCenter = theAOPtr->thePos.toQPointF();
    qreal myHalfW =  mySize.width() / 2.;
    qreal myHalfH =  mySize.height() / 2.;
    parentItem()->setX(myCenter.x() - myHalfW);
    parentItem()->setY(myCenter.y() - myHalfH);

    // TODO: Frame number
}

void ViewItem::setAbstractObjectPtr(AbstractObject *anAOPtr)
{
    assert (anAOPtr != nullptr);
    theAOPtr = anAOPtr;

    // TODO: retrieve image info
    //

    adjustObjectDrawingFromAO();
}


bool ViewItem::wouldBeColliding() const
{
    // TODO: coordinate conversion

    assert (theAOPtr != nullptr);
    return theAOPtr->isColliding(/*TODO: at Position XYAngle with size WxH */);
}
