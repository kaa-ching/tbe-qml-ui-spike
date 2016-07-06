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
      theActualQScreenPtr(nullptr),
      theWorldHeight(1.0), theWorldWidth(1.0)
{
    theRCSPtr = this;

    // TODO/FIXME: if there's more than one screen, which one are we on?
    theActualQScreenPtr = QApplication::primaryScreen();
    assert (theActualQScreenPtr != nullptr);
    printf("  physicX DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchX());
    printf("  physicY DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchY());

    theRenderPixels = theActualQScreenPtr->availableGeometry().width();
    theHandleHeight = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchX();
    if (theHandleHeight < theHandleMinPix)
        theHandleHeight = theHandleMinPix;
    theHandleWidth = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchY();
    if (theHandleWidth < theHandleMinPix)
        theHandleWidth = theHandleMinPix;

    connect (parent, &ResizingQuickWidget::wasResized,
             this, &ResolutionConversionSingleton::slot_RQW_resized);
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
    emit aspectRatioChanged();
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

void ResolutionConversionSingleton::slot_RQW_resized(QSize aNewSize)
{
    printf("RCS::slot_RQW_resized() called\n");
    // We want to draw World::width() on aNewSize.width() pixels which should
    // be the same as drawing World::height() on aNewSize.height() pixels.
    // Note that we already limit the RQW in aspect ratio.
}
