#include "AbstractObject.h"
#include "ViewItem.h"

ViewItem::ViewItem(QQuickItem *aParentPtr,
                       AbstractObject *anAOPtr)
                       : QQuickItem(aParentPtr), theAbstractObjectPtr(anAOPtr)
{
    // Nothing to do here...
}


void
ViewItem::adjustObjectDrawing(qreal aWidth_SI, qreal aHeight_SI, const Position &aCenter)
{
    // convert width and height from SI to pixels and set them
    QSize mySize = Vector(aWidth_SI, aHeight_SI).toQSize();
    parentItem()->setWidth(mySize.width());
    parentItem()->setHeight(mySize.height());

    // convert center position from SI to pixels and set the top-left position
    parentItem()->setRotation(aCenter.angleInDegrees());
    QPointF myCenter = aCenter.toQPointF();
    parentItem()->setX(myCenter.x());
    parentItem()->setY(myCenter.y());
}


bool ViewItem::wouldBeColliding()
{
    // TODO: coordinate conversion

    assert (Q_NULLPTR != theAbstractObjectPtr);
    return theAbstractObjectPtr->isColliding(/*TODO: at Position XYAngle with size WxH */);
}
