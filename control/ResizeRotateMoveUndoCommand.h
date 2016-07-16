#ifndef RESIZEROTATEMOVEUNDOCOMMAND_H
#define RESIZEROTATEMOVEUNDOCOMMAND_H

#include "AbstractUndoCommand.h"

class ResizeRotateMoveUndoCommand : public AbstractUndoCommand
{
public:
    explicit ResizeRotateMoveUndoCommand(AbstractObject *anAbstractObjectPtr);

    bool isChanged();
};

#endif // RESIZEROTATEMOVEUNDOCOMMAND_H
