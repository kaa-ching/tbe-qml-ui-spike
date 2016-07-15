#include "AbstractObject.h"
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

bool World::wouldBeColliding(const AbstractObject *anAOPtr, const Position& aPos, float aw, float ah) const
{
    // We're going to implement the Axis-Aligned Bounding Box (AABB) collision strategy for now:
    // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection .
    // That formula works with top-left corners, widths and heights.
    // Disadvantage: doesn't take non-rectangular shapes into account.
    // Using an AABB is an approximation at best anyway.

    assert(nullptr != anAOPtr);
    assert(std::end(theAOList) != std::find(std::begin(theAOList), std::end(theAOList), anAOPtr));
    qreal ax = aPos.x - aw/2.;
    qreal ay = aPos.y - ah/2.;

    // find the first colliding one
    for(auto& i : theAOList) {
        if (i != anAOPtr) {
            qreal ih = fabs(i->theHeight * cos(i->thePos.angle)) + fabs(i->theWidth * sin (i->thePos.angle));
            qreal iw = fabs(i->theHeight * sin(i->thePos.angle)) + fabs(i->theWidth * cos (i->thePos.angle));
            qreal ix = i->thePos.x - iw/2.;
            qreal iy = i->thePos.y - ih/2.;
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
