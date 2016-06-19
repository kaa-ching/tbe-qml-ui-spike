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
