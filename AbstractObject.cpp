#include "AbstractObject.h"
#include "ViewItem.h"
#include "World.h"

AbstractObject::AbstractObject(const QString &anImageName, const Position &aPosition, float aWidth, float aHeight)
    : theImageName(anImageName),
      thePos (aPosition),
      theWidth (aWidth),
      theHeight (aHeight),
      theWorldPtr(nullptr)
{
}


bool AbstractObject::isColliding() {
    assert(nullptr != theWorldPtr);
    return theWorldPtr->isColliding(this);
}


ViewItem *AbstractObject::createViewObject() {
    return nullptr;
}
