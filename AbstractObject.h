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

    /** returns the Name of the object, for users.
     *  If a non-US locale is specified, the returned string
     *  will already be translated
     */
    // TODO/FIXME: virtual const QString getName ( ) const = 0;
    virtual const QString getName ( ) const
        {return "BLOCK";}

    // TODO/FIXME: rename to getCenterPos()
    /// Get the Position of the object.
    /// This is the "original" center, i.e. where the object will
    /// be when not in simulation.
    /// @returns the value of theCenter
    virtual Position getOrigCenter ( ) const
    {
        return theCenter;
    }

    /// Get the value of theHeight
    /// @return the value of theHeight
    qreal getTheHeight ( ) const
    {
        return theHeight;
    }

    /// Get the value of theWidth
    /// @return the value of theWidth
    qreal getTheWidth ( ) const
    {
        return theWidth;
    }


    QString theImageName;

private:
    Position theCenter;
    float theWidth;
    float theHeight;

    World* theWorldPtr;
    friend class World;
    friend class ViewItem;
};

#endif // ABSTRACTOBJECT_H
