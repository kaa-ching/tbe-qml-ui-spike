/* The Butterfly Effect
 * This file copyright (C) 2011,2012,2016 Klaas van Gend
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation
 * applicable version is GPL version 2 only.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA.
 */

#ifndef ABSTRACTUNDOCOMMAND_H
#define ABSTRACTUNDOCOMMAND_H

#include "AbstractObject.h"
#include <QUndoCommand>

// forward declarations

/** this abstract class is the godfather of all undo classes
  */
class AbstractUndoCommand : public QUndoCommand
{
public:
    /// The constructor.
    explicit AbstractUndoCommand(AbstractObject *anAbstractObjectPtr,
                                 const QString &anUndoName,
                                 QUndoCommand *parent = 0);

    virtual ~AbstractUndoCommand();

    /// Call this member to cement this action into the undo stack
    /// and redo the last action to make sure the object is correct.
    /// @note Overridden in DummyUndoCommand.
    virtual void commit(void);

    /// Called by the Undo stack after the action of this
    /// class instance (Move/Rotate/Insert/Delete/Resize)
    /// is firstly done OR when it needs to be redone.
    void redo() override;

    /// Called by the Undo stack to undo the action specified in
    /// this command.
    void undo() override;

protected:
    /// pointer to the view object
    AbstractObject* theAOPtr;

    Position theOrigPos;
    Position theNewPos;

    qreal theOrigWidth;
    qreal theNewWidth;
    qreal theOrigHeight;
    qreal theNewHeight;

private:
    /// keep private & unimplemented: no default constructor
    AbstractUndoCommand();
    /// keep private & unimplemented: no copy constructor
    AbstractUndoCommand(AbstractUndoCommand &);
    /// keep private & unimplemented: no assignment operator
    AbstractUndoCommand &operator=(AbstractUndoCommand &);
};

#endif // ABSTRACTUNDOCOMMAND_H
