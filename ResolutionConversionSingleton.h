#ifndef RESOLUTIONCONVERSIONSINGLETON_H
#define RESOLUTIONCONVERSIONSINGLETON_H

#include <QObject>
#include <QMainWindow>

class QScreen;
class QQmlEngine;
class QJSEngine;

class ResolutionConversionSingleton : public QObject
{
    Q_OBJECT
public:
    explicit ResolutionConversionSingleton(QObject *parent = nullptr);

    /// @returns Width of a handle in pixels, depending on the DPI count of the display.
    Q_INVOKABLE int getHandleWidth();
    /// @returns Width of a handle in pixels, depending on the DPI count of the display.
    Q_INVOKABLE int getHandleHeight();

    static qreal convertPixels2H(qreal aPixelH);
    static qreal convertPixels2W(qreal aPixelW);
    static qreal convertPixels2X(qreal aPixelX);
    static qreal convertPixels2Y(qreal aPixelY);
    static qreal convertH2Pixels(qreal anSI_H);
    static qreal convertW2Pixels(qreal anSI_W);
    static qreal convertX2Pixels(qreal anSI_X);
    static qreal convertY2Pixels(qreal anSI_Y);

    static ResolutionConversionSingleton* me();

    /// Singletonprovider for interface to QML.
    /// Is registered with QML in constructor of MainWindow.
    static QObject* RCS_provider(QQmlEngine *engine, QJSEngine* scriptEngine)
    { Q_UNUSED(engine); Q_UNUSED(scriptEngine); return me(); }

signals:

public slots:
    void slot_screenAdded(QScreen *aScreen);
    void slot_screenRemoved(QScreen *aScreen);


private:
    QMainWindow* theMainWindowPtr;
    QScreen*     theActualQScreenPtr;
};

#endif // RESOLUTIONCONVERSIONSINGLETON_H
