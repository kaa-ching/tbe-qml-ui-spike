#ifndef RESOLUTIONCONVERSIONSINGLETON_H
#define RESOLUTIONCONVERSIONSINGLETON_H

#include <QObject>
#include <QMainWindow>

class QScreen;
class QQmlEngine;
class QJSEngine;
class ResizingQuickWidget;
class World;


class ResolutionConversionSingleton : public QObject
{
    Q_OBJECT
public:
    explicit ResolutionConversionSingleton(ResizingQuickWidget *parent);

    virtual ~ResolutionConversionSingleton();

    Q_PROPERTY(int handleWidth MEMBER theHandleWidth NOTIFY handleWidthChanged)
    Q_PROPERTY(int handleHeight MEMBER theHandleHeight NOTIFY handleHeightChanged)
    Q_PROPERTY(qreal renderPixels READ renderPixels NOTIFY renderPixelsChanged)
    Q_PROPERTY(qreal aspectRatio READ aspectRatio NOTIFY aspectRatioChanged)

    void adjustToWorldSize(const World& aWorldPtr);

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

    qreal renderPixels(void) { return theRenderPixels; }

    /// Calculates the aspect ratio, where 2.0 means "width=2.0*height".
    qreal aspectRatio(void) {return theWorldWidth / theWorldHeight; }

signals:
    void handleWidthChanged();
    void handleHeightChanged();
    void renderPixelsChanged();
    void aspectRatioChanged();

public slots:
    void slot_RQW_resized(QSize aNewSize);

private:
    QMainWindow* theMainWindowPtr;
    QScreen*     theActualQScreenPtr;

    int theHandleHeight;
    int theHandleWidth;

    /// The number of horizontal pixels in the QQuickView we calculate with.
    /// As such, we choose it to always be larger than the width of the screen
    /// to have enough resolution.
    /// @note: This will be a problem when we want to design levels larger
    ///        than a single screen.
    /// @note: Assuming landscape screens for now, playing this game in portrait
    ///        will just leave a part of the screen unused.
    qreal theRenderPixels;

    float theWorldHeight;
    float theWorldWidth;
};

#endif // RESOLUTIONCONVERSIONSINGLETON_H
