#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QQuickItem>
#include <Position.h>

class AbstractObject;

/// ViewItem is a member of the QML ViewObject class. We control the members
/// of ViewItem from C++.
/// @note The ViewItem is owned by the QQuickView, so you should pay attention
///       whether a ViewItem is still alive when needed.
class ViewItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit ViewItem(QQuickItem *aParentPtr = Q_NULLPTR);

//    /// based on changes in the underlying AbstractObject, adjust the image
//    /// by resizing and/or rotation. This is overkill for just moving...
//    /// @note This member should only be called by AbstractObject
//    /// @param aWidth_SI   width of object in meters
//    /// @param aHeight_SI  height of object in meters
//    /// @param aCenter     center of the object in meters/radians
//    virtual void adjustObjectDrawing(qreal aWidth_SI, qreal aHeight_SI, const Position &aCenter);

    /// Update drawing of the object based on the contents in the provided
    /// AbstractObject. Updated are: position (incl angle), width, height.
    /// TODO: image frame number, ZValue.
    void adjustObjectDrawingFromAO();

    /// Set the AbstractObject, read info from it.
    /// TODO: and retrieve the image information.
    void setAbstractObjectPtr(AbstractObject *anAOPtr);

    /// Returns whether the object _at the current location_ would be colliding.
//    Q_PROPERTY (bool isColliding READ isColliding NOTIFY CollidingChanged);

    bool isColliding();
    bool isColliding(const QRectF& anAABB, qreal anAngleDegrees);

    /// Returns an Axis-Aligned Bounding Box of the object.
    /// Use this for dragging: out-of-scene calculations.
    /// TODO: For now, this is based on the assumption that all objects are rectangles.
//    Q_PROPERTY(QRectF AABB READ AABB NOTIFY AABBChanged);

    QRectF AABB();

    /// retrieves a pointer to the 'theVI' object inside a ViewObject
    /// @returns nullptr if not found.
    static ViewItem *findVIinVO(QQuickItem* anVOPtr);

signals:
    /// SIGNAL
    /// Emitted whenever properties of the object change.
    /// Used by the Level creator to adjust the EditObjectDialog.
    /// @param anAOPtr pointer to the AbstractObject underneath.
//    void updateEditObjectDialog(AbstractObject *anAOPtr);

//    void AABBChanged();

public slots:
    /// SLOT, Signal from parent on any parameter change.
    /// will trigger (if needed):
    ///   * AABB recalculation
    void parentParamChanged();

public:
//private:
    /// because of the symbiosis between AbstractObject and ViewItem/ViewObject,
    /// we're not storing the shared_ptr, but TODO: a weak pointer
    /// (otherwise, no AbstractObject would ever be cleaned away)
    AbstractObject *theAOPtr;

    mutable bool wasColliding;
};

#endif // VIEWITEM_H
