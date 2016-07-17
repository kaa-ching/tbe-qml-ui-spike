#ifndef RESIZEROTATEMOVEUNDOCOMMAND_H
#define RESIZEROTATEMOVEUNDOCOMMAND_H

#include "AbstractUndoCommand.h"

class ResizeRotateMoveUndoCommand : public AbstractUndoCommand
{
public:
    explicit ResizeRotateMoveUndoCommand(AbstractObject *anAbstractObjectPtr);

    bool isChanged();

    /// Called by the Undo stack after the action of this
    /// class instance (Move/Rotate/Insert/Delete/Resize)
    /// is firstly done OR when it needs to be redone.
    void redo() override;

    /// Called by the Undo stack to undo the action specified in
    /// this command.
    void undo() override;

};

#endif // RESIZEROTATEMOVEUNDOCOMMAND_H
