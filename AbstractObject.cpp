#include "AbstractObject.h"
#include "ViewItem.h"
#include "ViewItemFactory.h"
#include "World.h"

AbstractObject::AbstractObject(const QString &anImageName, const Position &aPosition, float aWidth, float aHeight)
    : theImageName(anImageName),
      theCenter (aPosition),
      theWidth (aWidth),
      theHeight (aHeight),
      theVIPtr(nullptr),
      theWorldPtr(nullptr)
{
}


bool AbstractObject::wouldBeColliding(const Position& aPosition, float aWidth, float aHeight) const
{
    assert(nullptr != theWorldPtr);
    return theWorldPtr->wouldBeColliding(this, aPosition, aWidth, aHeight);
}


ViewItem *AbstractObject::createViewObject() {
    if (nullptr == theVIPtr)
    {
        theVIPtr = ViewItemFactory::me()->createViewItem(this);
    }
    return theVIPtr;
}
