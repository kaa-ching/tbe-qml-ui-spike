#include "ResizingQuickWidget.h"
#include "ResolutionConversionSingleton.h"

#include <QQuickItem>

ResizingQuickWidget::ResizingQuickWidget(QWidget *parent)
    : QQuickWidget(parent)
{
    // Note: this will only adjust the root object, it won't scale all objects in our view.
    // However, we have 'theScale' in the rootObject to take care of that.
    setResizeMode(QQuickWidget::SizeViewToRootObject);

    // register our resolution/scaling singleton
    theRCSPtr = new ResolutionConversionSingleton(this);
    qmlRegisterSingletonType<ResolutionConversionSingleton>("TBEView", 1, 0, "RCS", ResolutionConversionSingleton::RCS_provider);
}

int ResizingQuickWidget::heightForWidth(int w) const
{
    return w/theRCSPtr->aspectRatio();
}

void ResizingQuickWidget::resizeEvent(QResizeEvent *event)
{
    qreal myScaleX = width() / theRCSPtr->renderPixels();
    qreal myScaleY = height() / (theRCSPtr->renderPixels()/theRCSPtr->aspectRatio());
    if (myScaleY < myScaleX)
        myScaleX = myScaleY;
    rootObject()->setProperty("theScale", myScaleX);

    QQuickWidget::resizeEvent(event);
    emit wasResized(size());
}
