#ifndef WORLD_H
#define WORLD_H

#include <list>

class AbstractObject;


/** @abstract models the scene, contains all known objects and knows about the size.
 */
class World
{
public:
    World(float aWidth, float aHeight);

    void addObject(AbstractObject* anAOPtr);

    bool isColliding(AbstractObject* anAOPtr);

private:
    std::list<AbstractObject*> theAOList;

    float theWidth;
    float theHeight;
};

#endif // WORLD_H
