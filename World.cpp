#include "abstractobject.h"
#include "World.h"
#include <cassert>

World::World(float aWidth, float aHeight)
    : theWidth(aWidth), theHeight(aHeight), theWorldPtr(this)
{
}

World::~World()
{
    theWorldPtr = nullptr;
}

void World::addObject(AbstractObject *anAOPtr) {
    assert(std::end(theAOList) == std::find(std::begin(theAOList), std::end(theAOList), anAOPtr));

    anAOPtr->theWorldPtr = this;
    theAOList.push_back(anAOPtr);
}

bool World::isColliding(AbstractObject *anAOPtr) {
    // We're going to implement the Axis-Aligned Bounding Box (AABB) collision strategy for now:
    // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection .
    // Disadvantage: doesn't take non-rectangular shapes into account.

    assert(nullptr != anAOPtr);
    assert(std::end(theAOList) != std::find(std::begin(theAOList), std::end(theAOList), anAOPtr));
    // find the first colliding one
    for(auto& i : theAOList) {
        if (i != anAOPtr) {
            qreal ih = i->theHeight * cos(i->thePos.angle) + i->theWidth * sin (i->thePos.angle);
            qreal iw = i->theHeight * sin(i->thePos.angle) + i->theWidth * cos (i->thePos.angle);
            qreal ix = i->thePos.x - iw/2.;
            qreal iy = i->thePos.y - ih/2.;
            qreal ah = anAOPtr->theHeight * cos(anAOPtr->thePos.angle) + anAOPtr->theWidth * sin (anAOPtr->thePos.angle);
            qreal aw = anAOPtr->theHeight * sin(anAOPtr->thePos.angle) + anAOPtr->theWidth * cos (anAOPtr->thePos.angle);
            qreal ax = anAOPtr->thePos.x - aw/2.;
            qreal ay = anAOPtr->thePos.y - ah/2.;
            // thanks to the above short hand, this looks like the formula from the above link
            if ( ix < ax+aw &&
                 ix+iw > ax &&
                 iy < ay+ah &&
                 iy+ih > ay) {
                return true;
            }
        }
    }
    return false;
}
