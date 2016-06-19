#include "ViewItem.h"
#include "abstractobject.h"

ViewItem::ViewItem(QQuickItem *aParentPtr,
                       AbstractObject *anAOPtr)
                       : QQuickItem(aParentPtr), theAbstractObjectPtr(anAOPtr)
{

}


void
ViewItem::adjustObjectDrawing(qreal aWidth, qreal aHeight, const Position &aCenter)
{

}


bool ViewItem::wouldBeColliding()
{
    // TODO: coordinate conversion

    assert (Q_NULLPTR != theAbstractObjectPtr);
    return theAbstractObjectPtr->isColliding(/*TODO: at Position XYAngle with size WxH */);
}
