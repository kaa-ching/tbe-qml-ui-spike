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
    virtual void adjustObjectDrawing(qreal aWidth, qreal aHeight, const Position &aCenter);

signals:
    /// SIGNAL
    /// Emitted whenever properties of the object change.
    /// Used by the Level creator to adjust the EditObjectDialog.
    /// @param anAOPtr pointer to the AbstractObject underneath.
    void updateEditObjectDialog(AbstractObject *anAOPtr);

public slots:

private:
    /// because of the symbiosis between AbstractObject and ViewObject,
    /// we're not storing the shared_ptr, but the real pointer
    /// (otherwise, no AbstractObject would ever be cleaned away)
    AbstractObject *theAbstractObjectPtr;
};

#endif // VIEWITEM_H
