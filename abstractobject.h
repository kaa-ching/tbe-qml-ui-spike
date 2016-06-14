#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QString>
#include "Position.h"

class ViewObject;
class World;


class AbstractObject
{
public:
    AbstractObject(const QString& anImageName, const Position& aPosition, float aWidth, float aHeight);

    bool isColliding();

    ViewObject* createViewObject();

    QString theImageName;

    Position thePos;
    float theWidth;
    float theHeight;

    World* theWorldPtr;
    friend class World;
};

#endif // ABSTRACTOBJECT_H
