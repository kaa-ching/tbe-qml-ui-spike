#ifndef RESOLUTIONCONVERSIONSINGLETON_H
#define RESOLUTIONCONVERSIONSINGLETON_H

#include <QObject>
#include <QMainWindow>

class QScreen;
class QQmlEngine;
class QJSEngine;
class World;


class ResolutionConversionSingleton : public QObject
{
    Q_OBJECT
public:
    explicit ResolutionConversionSingleton(QObject *parent = nullptr);

    virtual ~ResolutionConversionSingleton();

    Q_PROPERTY(int handleWidth MEMBER theHandleWidth NOTIFY handleWidthChanged);
    Q_PROPERTY(int handleHeight MEMBER theHandleHeight NOTIFY handleHeightChanged);

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

signals:
    void handleWidthChanged();
    void handleHeightChanged();

public slots:
    void slot_screenAdded(QScreen *aScreen);
    void slot_screenRemoved(QScreen *aScreen);


private:
    QMainWindow* theMainWindowPtr;
    QScreen*     theActualQScreenPtr;

    int theHandleHeight;
    int theHandleWidth;

    float theWorldHeight;
    float theWorldWidth;
};

#endif // RESOLUTIONCONVERSIONSINGLETON_H
