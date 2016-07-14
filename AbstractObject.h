#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QString>
#include "Position.h"

class ViewItem;
class World;


class AbstractObject
{
public:
    AbstractObject(const QString& anImageName, const Position& aPosition, float aWidth, float aHeight);

    /// Check if this object at the given position and size would be colliding with any other object.
    /// @note: no checks for collisions with view here!
    /// @returns true if collision happens
    bool wouldBeColliding(const Position& aPosition, float aWidth, float aHeight) const;

    ViewItem* createViewObject();

    QString theImageName;

    Position thePos;
    float theWidth;
    float theHeight;

    World* theWorldPtr;
    friend class World;
};

#endif // ABSTRACTOBJECT_H
