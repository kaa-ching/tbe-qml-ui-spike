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

    theActualQScreenPtr = QApplication::primaryScreen();
    assert (theActualQScreenPtr != nullptr);
    printf("  physicX DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchX());
    printf("  physicY DPI: %f\n", theActualQScreenPtr->physicalDotsPerInchY());

    theRenderPixels = theActualQScreenPtr->availableGeometry().width();

    // Pre-calculate the handle sizes, they normally won't change during play...
    theHandleHeight = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchX();
    if (theHandleHeight < theHandleMinPix)
        theHandleHeight = theHandleMinPix;
    theHandleWidth = theHandleSizeMM / 25.4 * theActualQScreenPtr->physicalDotsPerInchY();
    if (theHandleWidth < theHandleMinPix)
        theHandleWidth = theHandleMinPix;

//    connect (parent, &ResizingQuickWidget::wasResized,
//             this, &ResolutionConversionSingleton::slot_RQW_resized);
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
    return aPixelH / (me()->theRenderPixels/me()->aspectRatio()) * me()->theWorldHeight;
}

qreal ResolutionConversionSingleton::convertPixels2W(qreal aPixelW)
{
    return aPixelW / me()->theRenderPixels * me()->theWorldWidth;
}

qreal ResolutionConversionSingleton::convertPixels2X(qreal aPixelX)
{
    return convertPixels2W(aPixelX);
}

qreal ResolutionConversionSingleton::convertPixels2Y(qreal aPixelY)
{
    return convertPixels2H(me()->theRenderPixels/me()->aspectRatio() - aPixelY);
}

qreal ResolutionConversionSingleton::convertH2Pixels(qreal anSI_H)
{
    return anSI_H/me()->theWorldHeight * (me()->theRenderPixels/me()->aspectRatio());
}

qreal ResolutionConversionSingleton::convertW2Pixels(qreal anSI_W)
{
    return anSI_W/me()->theWorldWidth * me()->theRenderPixels;
}

qreal ResolutionConversionSingleton::convertX2Pixels(qreal anSI_X)
{
    return convertH2Pixels(anSI_X);
}

qreal ResolutionConversionSingleton::convertY2Pixels(qreal anSI_Y)
{
    return me()->theRenderPixels/me()->aspectRatio() - convertH2Pixels(anSI_Y);
}


ResolutionConversionSingleton* ResolutionConversionSingleton::me()
{
    assert (theRCSPtr != nullptr);
    return theRCSPtr;
}

//void ResolutionConversionSingleton::slot_RQW_resized(QSize aNewSize)
//{
//    printf("RCS::slot_RQW_resized() called\n");
//    // We want to draw World::width() meters on aNewSize.width() pixels which should
//    // be the same as drawing World::height() meters on aNewSize.height() pixels.
//    // Note that we already limit the RQW in aspect ratio.
//    // But we get here because aNewSize [pixels] has changed.
//}
