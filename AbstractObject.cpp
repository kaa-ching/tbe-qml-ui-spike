#include "AbstractObject.h"
#include "ViewItem.h"
#include "World.h"

AbstractObject::AbstractObject(const QString &anImageName, const Position &aPosition, float aWidth, float aHeight)
    : theImageName(anImageName),
      theCenter (aPosition),
      theWidth (aWidth),
      theHeight (aHeight),
      theWorldPtr(nullptr)
{
}


bool AbstractObject::wouldBeColliding(const Position& aPosition, float aWidth, float aHeight) const
{
    assert(nullptr != theWorldPtr);
    return theWorldPtr->wouldBeColliding(this, aPosition, aWidth, aHeight);
}


ViewItem *AbstractObject::createViewObject() {
    // TODO: call ViewItemFactory from here
    return nullptr;
}
