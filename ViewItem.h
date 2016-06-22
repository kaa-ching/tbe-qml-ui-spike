#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QQuickItem>
#include <Position.h>

class AbstractObject;

class ViewItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit ViewItem(QQuickItem *aParentPtr = Q_NULLPTR, AbstractObject *anAOPtr = Q_NULLPTR);

    /// based on changes in the underlying AbstractObject, adjust the image
    /// by resizing and/or rotation. This is overkill for just moving...
    /// @note This member should only be called by AbstractObject
    /// @param aWidth_SI   width of object in meters
    /// @param aHeight_SI  height of object in meters
    /// @param aCenter     center of the object in meters/radians
    virtual void adjustObjectDrawing(qreal aWidth_SI, qreal aHeight_SI, const Position &aCenter);

    /// Returns whether the object _at the current location_ would be colliding.
    Q_INVOKABLE virtual bool wouldBeColliding();

signals:
    /// SIGNAL
    /// Emitted whenever properties of the object change.
    /// Used by the Level creator to adjust the EditObjectDialog.
    /// @param anAOPtr pointer to the AbstractObject underneath.
//    void updateEditObjectDialog(AbstractObject *anAOPtr);

public slots:

private:
    /// because of the symbiosis between AbstractObject and ViewObject,
    /// we're not storing the shared_ptr, but the real pointer
    /// (otherwise, no AbstractObject would ever be cleaned away)
    AbstractObject *theAbstractObjectPtr;
};

#endif // VIEWITEM_H
