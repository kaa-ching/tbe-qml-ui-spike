#ifndef VIEWITEMFACTORY_H
#define VIEWITEMFACTORY_H

#include "ResizingQuickWidget.h"
#include "ViewItem.h"

#include <QObject>
#include <QQuickWidget>

// TODO: maybe merge this class with ResizingQuickWidget later?
// TODO: or just make this an interface to that class?

/// The ViewItemFactory instantiates a QML ViewObject and its embedded ViewItem
/// objects. The ViewObject is part of the QML QQuickView, the ViewItem is
/// returned as we control the ViewObject through the ViewItem.
class ViewItemFactory : public QObject
{
    Q_OBJECT
public:
    explicit ViewItemFactory(QQuickWidget *parent = 0);

    /// Create a ViewObject (QML) and a ViewItem (C++) and make sure they get
    /// updated with the contents of anAOPtr.
    /// @param anAOPtr Pointer to an AbstractObject.  TODO: shared_ptr???
    ViewItem *createViewItem(AbstractObject *anAOPtr);

    //TODO: we probably need this member later...
    // @note: this function is very likely expensive
    //bool doesViewItemStillExist(ViewItem* aPtr);

signals:

public slots:

private:
    /// pointer to the ResizingQuickWidget.
    QQuickWidget *theRQWPtr;
};

#endif // VIEWITEMFACTORY_H
