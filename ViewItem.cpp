#include "ViewItem.h"
#include "abstractobject.h"

ViewItem::ViewItem(QQuickItem *aParentPtr,
                       AbstractObject *anAOPtr)
                       : QQuickItem(aParentPtr), theAbstractObjectPtr(anAOPtr)
{
    printf("hello from ViewItem::ViewItem\n");
}


void
ViewItem::adjustObjectDrawing(qreal aWidth_SI, qreal aHeight_SI, const Position &aCenter)
{
    parentItem()->setWidth(aWidth_SI);
    parentItem()->setHeight(aHeight_SI);
}


bool ViewItem::wouldBeColliding()
{
    // TODO: coordinate conversion

    assert (Q_NULLPTR != theAbstractObjectPtr);
    return theAbstractObjectPtr->isColliding(/*TODO: at Position XYAngle with size WxH */);
}
