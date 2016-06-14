#ifndef WORLD_H
#define WORLD_H

#include <list>

class AbstractObject;

class World
{
public:
    World();

    void addObject(AbstractObject* anAOPtr);

    bool isColliding(AbstractObject* anAOPtr);

    std::list<AbstractObject*> theAOList;
};

#endif // WORLD_H
