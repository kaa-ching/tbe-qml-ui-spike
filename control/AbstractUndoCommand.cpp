/* The Butterfly Effect
 * This file copyright (C) 2011,2016 Klaas van Gend
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

#include "AbstractUndoCommand.h"
#include "UndoSingleton.h"

AbstractUndoCommand::AbstractUndoCommand(AbstractObject *anAbstractObjectPtr,
                                         const QString &anUndoName,
                                         QUndoCommand *parent)
    : QUndoCommand(parent), theAOPtr(anAbstractObjectPtr)
{
    // This is the undo action, anUndoName is e.g. “Move %s” and
    // myObjectPtr->getName() is e.g. “Birch Bar”
    setText( anUndoName.arg(theAOPtr->getName()));
    theOrigPos    = theNewPos    = theAOPtr->getOrigCenter();
    theOrigWidth  = theNewWidth  = theAOPtr->getTheWidth();
    theOrigHeight = theNewHeight = theAOPtr->getTheHeight();
}


AbstractUndoCommand::~AbstractUndoCommand()
{
    UndoSingleton::notifyGone(this);
}


void AbstractUndoCommand::commit(void)
{
    UndoSingleton::push(this);
}


void AbstractUndoCommand::redo(void)
{
    // in the case of DeleteUndoCommand, we won't have a ViewObject left
    // when we get here ;-)
//    if (theViewObjPtr) {
//        theViewObjPtr->setNewGeometry(theNewPos, theNewWidth, theNewHeight);
//    }
}


void AbstractUndoCommand::undo(void)
{
    // in the case of InsertUndoCommand, we won't have a ViewObject left
    // when we get here ;-)
//    if (theViewObjPtr) {
//        theViewObjPtr->setNewGeometry(theOrigPos, theOrigWidth, theOrigHeight);
//    }
}
