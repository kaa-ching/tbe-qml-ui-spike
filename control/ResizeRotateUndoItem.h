#ifndef RESIZEROTATEUNDOITEM_H
#define RESIZEROTATEUNDOITEM_H

#include "ResizeRotateMoveUndoCommand.h"
#include <QQuickItem>

/// An instance of this class gets instantiated every time a ResizeRotate item
/// gets created. It will be destroyed upon destruction as well.
/// The RRUI has a QUndoCommand, that it will populate. Upon destruction, it
/// will make the decision whether to push the QUndoCommand or just destroy it
/// when nothing really changed.
class ResizeRotateUndoItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* theDecorated MEMBER theDecoratedPtr NOTIFY theDecoratedChanged)

public:
    explicit ResizeRotateUndoItem(QQuickItem *parent = nullptr);
    virtual ~ResizeRotateUndoItem();

signals:
    void theDecoratedChanged();

public slots:
    void slot_parentChanged();

private:
    ResizeRotateMoveUndoCommand *theRRMUCPtr;
    QQuickItem* theDecoratedPtr;

//    Position lastKnownGoodPos;
//    qreal    lastKnownGoodHeight;
//    qreal    lastKnownGoodWidth;
};

#endif // RESIZEROTATEUNDOITEM_H
