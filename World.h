#ifndef WORLD_H
#define WORLD_H

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

    bool isColliding(AbstractObject* anAOPtr);

    float getWidth() const {return theWidth; }
    float getHeight() const { return theHeight; }

private:
    std::list<AbstractObject*> theAOList;

    float theWidth;
    float theHeight;

    World* theWorldPtr = nullptr;
};

#endif // WORLD_H
