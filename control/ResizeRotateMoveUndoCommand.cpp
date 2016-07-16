#include "ResizeRotateMoveUndoCommand.h"

ResizeRotateMoveUndoCommand::ResizeRotateMoveUndoCommand(AbstractObject *anAbstractObjectPtr)
    : AbstractUndoCommand(anAbstractObjectPtr, QObject::tr("AbstractResizeRotateMove %1"), nullptr)
{

}

bool ResizeRotateMoveUndoCommand::isChanged()
{
    theNewPos = theAOPtr->getOrigCenter();
    theNewWidth = theAOPtr->getTheWidth();
    theNewHeight= theAOPtr->getTheHeight();

    if (theOrigPos != theNewPos)
        return true;
    if (theOrigHeight != theNewHeight)
        return true;
    if (theOrigWidth != theNewWidth)
        return true;
    return false;
}
