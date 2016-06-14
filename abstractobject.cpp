#include "abstractobject.h"
#include "viewobject.h"
#include "world.h"

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


ViewObject *AbstractObject::createViewObject() {
    return nullptr;
}
