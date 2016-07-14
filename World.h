#ifndef WORLD_H
#define WORLD_H

#include "Position.h"
#include <list>

class AbstractObject;


/** @abstract models the scene, contains all known objects and knows about the size.
 */
class World
{
public:
    explicit World(float aWidth, float aHeight);
    ~World();

    void addObject(AbstractObject* anAOPtr);

    /// Checks whether object pointed to by anAOPtr would be colliding with any other objects
    /// if it would be at position aPos with size aWidthxaHeight.
    /// @returns true if this object would be colliding.
    bool wouldBeColliding(const AbstractObject* anAOPtr, const Position& aPos, float aWidth, float aHeight) const;

    float getWidth() const {return theWidth; }
    float getHeight() const { return theHeight; }

private:
    std::list<AbstractObject*> theAOList;

    float theWidth;
    float theHeight;

    World* theWorldPtr = nullptr;
};

#endif // WORLD_H
