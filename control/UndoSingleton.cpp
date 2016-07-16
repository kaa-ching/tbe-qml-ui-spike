/* The Butterfly Effect
 * This file copyright (C) 2011 Klaas van Gend
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

#include "UndoSingleton.h"
#include "ResizeRotateMoveUndoCommand.h"

static UndoSingleton *theUndoSingletonPtr = nullptr;
static AbstractUndoCommand *theCurrentlyActiveUndoCommand = nullptr;


UndoSingleton::UndoSingleton(void)
{
    // nothing to do
}


void UndoSingleton::clear()
{
    delete theCurrentlyActiveUndoCommand;
    theCurrentlyActiveUndoCommand = nullptr;
    me()->theUndoStack.clear();
}


QAction *UndoSingleton::createRedoAction (QObject *parent, const QString &prefix)
{
    return me()->theUndoStack.createRedoAction(parent, prefix);
}


QAction *UndoSingleton::createUndoAction (QObject *parent, const QString &prefix)
{
    return me()->theUndoStack.createUndoAction(parent, prefix);
}


AbstractUndoCommand *
UndoSingleton::createUndoCommand(AbstractObject* anAOPtr,
                                 ActionType anUndoType)
{
    AbstractUndoCommand *myNewCommand = nullptr;
    // return immediately for UndoActions that do not need further
    // user interactions (i.e. those derived from Dummy).
    switch (anUndoType) {
    case ACTION_INSERT:
//        return new InsertUndoCommand(anObject);
        break;
    case ACTION_MOVE:
//        myNewCommand = new MoveUndoCommand(anObject);
        break;
    case ACTION_RESIZEROTATE:
        myNewCommand =  new ResizeRotateMoveUndoCommand(anAOPtr);
        break;
    case ACTION_SETPHONE:
//        return new ChoosePhoneUndoCommand(anObject);
        break;
    case ACTION_DELETE:
//        return new DeleteUndoCommand(anObject);
        break;
    case ACTION_EDITPROPERTIES:
//        return new EditPropertyUndoCommand(anObject);
        break;
        //case ActionIcon::ACTION_EDITSPECIAL:
        // TODO/FIXME
        //break;
    }
    if (theCurrentlyActiveUndoCommand != nullptr)
        delete theCurrentlyActiveUndoCommand;
    theCurrentlyActiveUndoCommand = myNewCommand;
    return myNewCommand;
}


bool UndoSingleton::isClean()
{
    return me()->theUndoStack.isClean();
}


UndoSingleton *UndoSingleton::me(void)
{
    if (theUndoSingletonPtr == nullptr)
        theUndoSingletonPtr = new UndoSingleton();
    return theUndoSingletonPtr;
}


void UndoSingleton::notifyGone(AbstractUndoCommand *anAUCPtr)
{
    if (anAUCPtr == theCurrentlyActiveUndoCommand)
        theCurrentlyActiveUndoCommand = nullptr;
}


void UndoSingleton::push(AbstractUndoCommand *anAUCPtr)
{
    printf("Undo Singleton: '%s'\n", anAUCPtr->text().toLatin1().constData());
    me()->theUndoStack.push(anAUCPtr);
    notifyGone(anAUCPtr);
}


void UndoSingleton::setClean()
{
    me()->theUndoStack.setClean();
}
