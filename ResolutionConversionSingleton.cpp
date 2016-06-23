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

qreal ResolutionConversionSingleton::convertPixels2H(qreal aPixelH)
{
    // TODO/FIXME: implement
    return aPixelH/50.;
}

qreal ResolutionConversionSingleton::convertPixels2W(qreal aPixelW)
{
    // there's no
    return convertPixels2X(aPixelW);
}

qreal ResolutionConversionSingleton::convertPixels2X(qreal aPixelX)
{
    // TODO/FIXME: implement
    return aPixelX/50.;
}

qreal ResolutionConversionSingleton::convertPixels2Y(qreal aPixelY)
{
    // TODO/FIXME: implement
    return convertPixels2H(500.-aPixelY);
}

qreal ResolutionConversionSingleton::convertH2Pixels(qreal anSI_H)
{
    // TODO/FIXME: implement
    return anSI_H*50;
}

qreal ResolutionConversionSingleton::convertW2Pixels(qreal anSI_W)
{
    // TODO/FIXME: implement
    return anSI_W*50.0;
}

qreal ResolutionConversionSingleton::convertX2Pixels(qreal anSI_X)
{
    // TODO/FIXME: implement
    return anSI_X*50;
}

qreal ResolutionConversionSingleton::convertY2Pixels(qreal anSI_Y)
{
    // TODO/FIXME: implement
    return 500-convertH2Pixels(anSI_Y);
}


ResolutionConversionSingleton* ResolutionConversionSingleton::me()
{
    assert (theRCSPtr != nullptr);
    return theRCSPtr;
}
