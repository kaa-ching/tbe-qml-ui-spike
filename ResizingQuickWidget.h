#ifndef RESIZINGQUICKWIDGET_H
#define RESIZINGQUICKWIDGET_H

#include "ResolutionConversionSingleton.h"

#include <QQuickWidget>

class ResizingQuickWidget : public QQuickWidget
{
    Q_OBJECT
public:
    ResizingQuickWidget(QWidget *parent = Q_NULLPTR);

    /// Overridden from QWidget to maintain aspect ratio.
    virtual bool	hasHeightForWidth() const override
    { return true; }

    /// Overridden from QWidget to maintain aspect ratio.
    virtual int heightForWidth(int w) const override;

    /// Set the aspect ratio, where 2.0 means "width=2.0*height".
    void setAspectRatio (qreal aRatio);

signals:
    void wasResized(QSize aNewSize);

public slots:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    qreal theAspectRatio;

    /// pointer to our "singleton" that handles resolution and coordinate conversion
    ResolutionConversionSingleton* theRCSPtr;
};

#endif // RESIZINGQUICKWIDGET_H
