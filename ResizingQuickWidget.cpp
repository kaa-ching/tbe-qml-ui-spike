#include "ResizingQuickWidget.h"
#include "ResolutionConversionSingleton.h"

#include <QQuickItem>

ResizingQuickWidget::ResizingQuickWidget(QWidget *parent)
    : QQuickWidget(parent),
      theAspectRatio(2.0)
{
    // note: this will only adjust the root object, it won't scale all objects in our view.
    setResizeMode(QQuickWidget::SizeRootObjectToView);

    // register our resolution/scaling singleton
    theRCSPtr = new ResolutionConversionSingleton(this);
    qmlRegisterSingletonType<ResolutionConversionSingleton>("TBEView", 1, 0, "RCS", ResolutionConversionSingleton::RCS_provider);
}

int ResizingQuickWidget::heightForWidth(int w) const
{
    return w/theAspectRatio;
}

void ResizingQuickWidget::resizeEvent(QResizeEvent *event)
{
    // Let's assume we always draw the scene as 1000x500
    //   (i.e. what's set as background in the main.qml file).
    // If there are not exactly 1000 pixels horizontal, or 500 vertical,
    // we need to scale.

    qreal myScaleX = width() / 1000.;
    qreal myScaleY = height() / 500.;
    if (myScaleY < myScaleX)
        myScaleX = myScaleY;
    rootObject()->setProperty("theScale", myScaleX);

    QQuickWidget::resizeEvent(event);
    // emit wasResized(size());
}

void ResizingQuickWidget::setAspectRatio(qreal aRatio)
{
    // sanity check, don't want negative numbers or near-divide-by-zeros
    if (aRatio < 0.1)
        aRatio = 0.1;
    theAspectRatio = aRatio;
}
