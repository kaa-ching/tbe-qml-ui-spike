/* The Butterfly Effect
 * This file copyright (C) 2009,2010,2012,2016  Klaas van Gend
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

#ifndef POSITION_H
#define POSITION_H

//#include "tbe_global.h"
#include <cassert>
#include <cmath>
#include <QPointF>
#include <QSize>
#include <QRectF>

#define PI 3.1415926535

struct b2Vec2;
class Position;

// COORDINATE SYSTEMS IN TBE
//
// * Box2D and TBE Model share the same, SI units [m] based, coordinate system.
//   A positive y is pointing upwards.
//   * (0.0, World::height) is at the top-left
//   * (World::width, 0.0) is at the bottom-right of the screen, not counting padding
//     * padding always happens at either the right or the bottom
//   - b2Vec2 is the Box2D vector type
//   - Vector is the TBE Model vector type
//   - Position is the TBE Model "vector from (0,0) to center of object plus angle" type
//
// * QQuickWidget uses a PIXEL-based coordinate system
//   A positive y is pointing down.
//   (0,0) is top-left  *** (TODO/FIXME: maybe including the title bar, menu and toolbar?)
//   (QQuickView::width, QQuickView::height) is the bottom-right
//   Even worse: QQuickWidget assumes rotation to be positive CLOCKWISE,
//   i.e. against normal mathematical definitions...
//
// - constructors with QPointF assume conversion from QQuickView to TBEModel
// - toQPointF() members assume conversion from TBEModel to QQuickView
// - toQSize() members assume conversion from TBEModel to QQuickView
// - tob2Vec2() members only create a different type, no calculations

/// Compare two QReals
/// @returns true if they are similiar within Position::minimalMove.
bool areQRealsTheSame(qreal anA, qreal aB);

class Vector
{
public:
    // obvious constructors
    Vector (void);
    Vector (qreal aDX, qreal aDY);
    Vector (const QPointF &aPoint);
    Vector (const QSizeF &aSize);
    Vector (const b2Vec2 &aVec);

    /// Constructor ignores the angle from the Position.
    /// Think twice before using this one - physically it makes no sense!
    Vector (const Position &aPosition);

    /// Constructs a vector of length 1 in direction anAngle.
    Vector (qreal anAngle);

    /// @returns The length of the Vector.
    qreal length(void) const;

    /// @returns The angle of the Vector with the positive X axis.
    qreal    toAngle(void) const;

    /// @returns The vector in Box2D type.
    b2Vec2   toB2Vec2(void) const;

    /// @returns A Position instance, where the Vector is interpreted to be
    /// pointing from (0,0) and the angle is zero.
    Position toPosition(void) const;

    /// @returns This vector, interpreted with the QQuickView dimensions in mind
    /// i.e. x and y are scaled and y is inverted.
    QPointF  toQPointF(void) const;

    /// @returns This vector, interpreted with the QQuickView dimensions in mind
    /// i.e. x and y are scaled and the abs() value is given.
    QSize    toQSize(void) const;

    /// @returns A QString representation of the Vector, useful for debugging.
    QString  toString(void) const;

    /// @returns a Vector in the same direction, but with length one.
    Vector   toUnitVector(void) const;

    /// @returns This vector, rotated along anAngle.
    /// @param anAngle      Angle in radians.
    Vector rotate(qreal anAngle) const;

    /** Converts a string in format "(0.0,0.0)" into this Vector
      * If the conversion is not successful, the Vector is not modified.
      * @param aString the string to convert
      * @returns true if conversion successful.
      */
    bool fromString(QString aString);

    qreal dx;
    qreal dy;
};

/**
  * class Position
  *
  * This class abstracts the Position - x,y,angle
  */
class Position
{
public:

    // Constructors/Destructors

    /**
     * Constructor - set x (m), y(m), angle(radial)
     */
    Position (qreal anX = NAN, qreal aY = NAN, qreal anAngle = 0.0);

    /// Constructor, will create position at center of QRectF (and convert coordinates).
    Position (const QRectF &aPoint, qreal anAngleInDegrees = 0.0);
    /// Constructor, will create position at aPoint (and convert coordinates).
    Position (const QPointF &aPoint, qreal anAngleInDegrees = 0.0);
    /// Constructor, will create position at aPoint (and NOT convert coordinates).
    Position (const Vector &aPoint, qreal anAngle = 0.0);
    /// Constructor, will create position at aVec (and NOT convert coordinates).
    Position (const b2Vec2 &aVec, qreal anAngle = 0.0);

    // Public attributes

    /// x-coordinate: x=0 is lower left corner, positive is right. unit: meter
    qreal x;

    /// y-coordinate: y=0 is lower left corner, positive is up. unit: meter
    qreal y;

    /// angle coordinate: angle=0 is positive x direction, turning counterclockwise. unit: 2Pi for a full turn
    qreal angle;

    const static qreal minimalMove;
    const static qreal minimalRot;

    /// @returns true if Position exists, or false if used uninitialised
    bool isValid() const
    {
        return (false == std::isnan(x) && false == std::isnan(y));
    }

    b2Vec2  toB2Vec2(void) const;
    QPointF toQPointF(void) const;
    QString toString(void) const;
    Vector  toVector(void) const
    {
        assert(isValid());
        return Vector(*this);
    }

    qreal angleInDegrees(void) const
    {
        return -angle * 180 / PI;
    }

    qreal length(void);
};


/** add a Vector to a Position
 *  - that implies that the vector is multiplied with the angle
 *    i.e. in the local object coordinates
 */
Position operator+(const Position &p1, const Vector &v1);
/// subtracts Vector from a Position
Position operator-(const Position &p1, const Vector &v1);

/// add Position and QPointF
Position operator+(const Position &p1, const QPointF &p2);
/// subtracts Position and QPointF
Position operator+(const Position &p1, const QPointF &p2);

/// adds a Vector to a Vector
Vector operator+(const Vector &v1, const Vector &v2);

/// subtracts two Vectors
Vector operator-(const Vector &p1, const Vector &p2);

/// constant multiplies vector
Vector operator*(const qreal c1, const Vector &p1);

/// scale - Vector multiplies Vector into a Vector
Vector operator*(const Vector &v1, const Vector &v2);

/// compare two positions
bool operator==(const Position &p1, const Position &p2);
bool operator!=(const Position &p1, const Position &p2);

/// compare two vectors
bool operator==(const Vector &p1, const Vector &v2);
bool operator!=(const Vector &p1, const Vector &v2);

/// send to debug directly
QDebug operator<<(QDebug dbg, const Position &p);
QDebug operator<<(QDebug dbg, const Vector &v);

#endif // POSITION_H
