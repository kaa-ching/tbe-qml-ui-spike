#include "ResolutionConversionSingleton.h"
#include <cassert>

static ResolutionConversionSingleton *theRCSPtr = nullptr;

ResolutionConversionSingleton::ResolutionConversionSingleton(QObject *parent) : QObject(parent)
{
    theRCSPtr = this;
}

int ResolutionConversionSingleton::getHandleWidth()
{
    // TODO/FIXME: make this flexible for High-DPI screens later
    return 24;
}

int ResolutionConversionSingleton::getHandleHeight()
{
    // TODO/FIXME: make this flexible for High-DPI screens later
    return 24;
}

qreal ResolutionConversionSingleton::convertPixels2X(qreal aPixelX)
{
    // TODO/FIXME: implement
    return aPixelX;
}

qreal ResolutionConversionSingleton::convertPixels2Y(qreal aPixelY)
{
    // TODO/FIXME: implement
    return aPixelY;
}

qreal ResolutionConversionSingleton::convertX2Pixels(qreal anSI_X)
{
    // TODO/FIXME: implement
    return anSI_X;
}

qreal ResolutionConversionSingleton::convertY2Pixels(qreal anSI_Y)
{
    // TODO/FIXME: implement
    return anSI_Y;
}


ResolutionConversionSingleton* ResolutionConversionSingleton::me()
{
    assert (theRCSPtr != nullptr);
    return theRCSPtr;
}
