#include "AbstractObject.h"
#include "ResolutionConversionSingleton.h"
#include "ViewItem.h"

ViewItem::ViewItem(QQuickItem *aParentPtr)
                       : QQuickItem(aParentPtr),
                         theAOPtr(nullptr),
                         wasColliding(false)
{
    // Nothing to do here...
}


// TODO: create a destructor, because we need to take the AO from the world upon destruction.

QRectF
ViewItem::AABB()
{
    // parentItem.boundingRect() only addresses the size, it doesn't have the coordinates.
    QRectF myBB = parentItem()->boundingRect();
    qreal  myCX  = parentItem()->x() + 0.5*myBB.width();
    qreal  myCY  = parentItem()->y() + 0.5*myBB.height();
    qreal  myA   = -parentItem()->rotation() * PI / 180; // in radians

    // adjusted (for rotation) width and height
    qreal myAW = fabs(myBB.width()*cos(myA)) + fabs(myBB.height()*sin(myA));
    qreal myAH = fabs(myBB.width()*sin(myA)) + fabs(myBB.height()*cos(myA));

    QRectF myResult(myCX-.5*myAW, myCY-.5*myAH,
                    myAW, myAH );
    return myResult;
}

void
ViewItem::adjustObjectDrawingFromAO()
{
    assert(theAOPtr!=nullptr);

    connect (parentItem(), SIGNAL(heightChanged()), this, SLOT(parentParamChanged()));
    connect (parentItem(), SIGNAL(widthChanged()),  this, SLOT(parentParamChanged()));
    connect (parentItem(), SIGNAL(xChanged()),      this, SLOT(parentParamChanged()));
    connect (parentItem(), SIGNAL(yChanged()),      this, SLOT(parentParamChanged()));
    connect (parentItem(), SIGNAL(zChanged()),      this, SLOT(parentParamChanged()));
    connect (parentItem(), SIGNAL(rotationChanged()),this,SLOT(parentParamChanged()));

    // convert width and height from SI to pixels and set them
    QSize mySize = Vector(theAOPtr->theWidth, theAOPtr->theHeight).toQSize();
    parentItem()->setWidth(mySize.width());
    parentItem()->setHeight(mySize.height());

    // convert center position from SI to pixels and set the top-left position
    parentItem()->setRotation(theAOPtr->thePos.angleInDegrees());
    QPointF myCenter = theAOPtr->thePos.toQPointF();
    qreal myHalfW =  mySize.width() / 2.;
    qreal myHalfH =  mySize.height() / 2.;
    parentItem()->setX(myCenter.x() - myHalfW);
    parentItem()->setY(myCenter.y() - myHalfH);

    // TODO: Frame number
}

bool
ViewItem::isColliding()
{
    return isColliding(AABB(), parentItem()->rotation());
}

bool
ViewItem::isColliding(const QRectF& anAABB, qreal anAngleDegrees)
{
    bool myResult = false;

    //** check for collisions with the widget boundaries
    qreal myWidth = ResolutionConversionSingleton::me()->renderPixels();
    qreal myHeight= ResolutionConversionSingleton::me()->renderPixels()/ResolutionConversionSingleton::me()->aspectRatio();
    // left
    if (anAABB.contains(0, anAABB.center().y()))         myResult=true;
    // top
    if (anAABB.contains(anAABB.center().x(), 0))         myResult=true;
    // bottom
    if (anAABB.contains(anAABB.center().x(), myHeight))  myResult=true;
    // right
    if (anAABB.contains(myWidth,anAABB.center().y()))    myResult=true;

    //** check for collisions with any other objects
    if (theAOPtr != nullptr)
    {
        if (theAOPtr->wouldBeColliding( Position(anAABB, anAngleDegrees),
                                        ResolutionConversionSingleton::me()->convertPixels2W(anAABB.width()),
                                        ResolutionConversionSingleton::me()->convertPixels2H(anAABB.height())))
            myResult = true;
    }

    if (myResult != wasColliding)
    {
        parentItem()->setProperty("isColliding", myResult);
    }
    wasColliding = myResult;
    return myResult;
}

void
ViewItem::parentParamChanged()
{
    // will adjust isColliding property in parentItem when needed
    isColliding();
}


void ViewItem::setAbstractObjectPtr(AbstractObject *anAOPtr)
{
    assert (anAOPtr != nullptr);
    theAOPtr = anAOPtr;

    // TODO: retrieve image info
    //

    // TODO: update isHResize / isVResize / isRotate
    rand();
    parentItem()->setProperty("isHResize", true); //rand() % 2);
    parentItem()->setProperty("isVResize", true); // rand() % 2);
    parentItem()->setProperty("isRotate", true); // rand() % 2);

    adjustObjectDrawingFromAO();
}
