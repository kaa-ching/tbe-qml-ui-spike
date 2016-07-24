#include "ResizeRotateUndoItem.h"
#include "UndoSingleton.h"
#include "ViewItem.h"

ResizeRotateUndoItem::ResizeRotateUndoItem(QQuickItem *parent)
    : QQuickItem(parent),
    theRRMUCPtr(nullptr)
{
    assert(parent == nullptr);
    // Once theDecorated is set, we want to know so we can create
    // our UndoCommand and have it grab the initial data.
    connect(this, SIGNAL(theDecoratedChanged()), this, SLOT(slot_parentChanged()));
}


ResizeRotateUndoItem::~ResizeRotateUndoItem()
{
    assert (nullptr != theRRMUCPtr);

    //*** Is changed? then push to undocommand stack
    if (theRRMUCPtr->isChanged())
        theRRMUCPtr->commit();
    else
        delete theRRMUCPtr;
}


void ResizeRotateUndoItem::slot_parentChanged()
{
    // We need access to the ViewItem: the 'theVI' child of 'theDecorated'.
    ViewItem* myVIPtr = ViewItem::findVIinVO(theDecoratedPtr);
    assert (myVIPtr!=nullptr);
    assert (myVIPtr->theAOPtr != nullptr);
    theRRMUCPtr = dynamic_cast<ResizeRotateMoveUndoCommand*>(UndoSingleton::createUndoCommand(myVIPtr->theAOPtr, UndoSingleton::ACTION_RESIZEROTATE));
}


qreal ResizeRotateUndoItem::vector2AngleDegrees(qreal x, qreal y)
{
    Vector myVector( QSizeF(x, -y) );
    printf("myVector: (%f,%f)\n", myVector.dx, myVector.dy);
    return myVector.toAngle()* 180/PI;
}
