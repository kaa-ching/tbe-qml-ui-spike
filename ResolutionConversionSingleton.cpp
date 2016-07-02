#include "ResolutionConversionSingleton.h"
#include "ResizingQuickWidget.h"
#include "World.h"
#include <cassert>

#include <QWindow>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>


// TODO: make configurable using QSettings
static const qreal theHandleSizeMM = 4.; // handle is resolution independent, 4mm wide and tall
static const int   theHandleMinPix = 18; // never make handle smaller than 18 pixels


static ResolutionConversionSingleton *theRCSPtr = nullptr;

ResolutionConversionSingleton::ResolutionConversionSingleton(ResizingQuickWidget *parent)
    : QObject(parent),
      theActualQScreenPtr(nullptr)
{
    theRCSPtr = this;

    // TODO/FIXME: if there's more than one screen, which one are we on?
    printf("number of screens: %d\n", QApplication::screens().count());
    theActualQScreenPtr = QApplication::screens().at(0);
    assert (theActualQScreenPtr != nullptr);
    printf("  name:  '%s'\n", theActualQScreenPtr->name().toLatin1().constData());
    printf("  logical DPI: %f\n", theActualQScreenPtr->logicalDotsPerInchX());
    printf("  physicX DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchX());
    printf("  physicY DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchY());
    printf("  screen res: %dx%d pix\n", theActualQScreenPtr->availableSize().width(), theActualQScreenPtr->availableSize().height());
    printf("  screen dim: %fx%f mm\n", theActualQScreenPtr->physicalSize().width(), theActualQScreenPtr->physicalSize().height());

    theHandleHeight = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchX();
    if (theHandleHeight < theHandleMinPix)
        theHandleHeight = theHandleMinPix;
    theHandleWidth = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchY();
    if (theHandleWidth < theHandleMinPix)
        theHandleWidth = theHandleMinPix;

    connect (qApp, &QGuiApplication::screenAdded,
             this, &ResolutionConversionSingleton::slot_screenAdded);
    connect (qApp, &QGuiApplication::screenRemoved,
             this, &ResolutionConversionSingleton::slot_screenRemoved);
}


ResolutionConversionSingleton::~ResolutionConversionSingleton()
{
    theMainWindowPtr = nullptr;
    theActualQScreenPtr  = nullptr;
}

void ResolutionConversionSingleton::adjustToWorldSize(const World &aWorldPtr)
{
    theWorldHeight = aWorldPtr.getHeight();
    theWorldWidth  = aWorldPtr.getWidth();
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

// TODO/FIXME: don't work on Linux
void ResolutionConversionSingleton::slot_screenAdded(QScreen *aScreen)
{
    printf("screen added\n");
}

// TODO/FIXME: don't work on Linux
void ResolutionConversionSingleton::slot_screenRemoved(QScreen *aScreen)
{
    printf("screen deleted\n");
}
