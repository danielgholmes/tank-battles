//! An Abstract-based class forming an interface for all Moveable objects within the game.
/*! This class is used as an interfacing template by all objects which are capable of
    moving. Movable classes are handled by the move manager
    who has access to all member functions within this class interface.
    \class  Movable
    \file   Moveable.h
    \author Daniel Holmes & Jonathan Gerrand
    \date   2 September 2014
 */

#ifndef MOVABLE_H_
#define MOVABLE_H_

//Includes
#include "Deletable.h"
#include "Structures.h"
//Defines
#define PI          3.141592653589793238462643383279502884L

class Movable: virtual public Deletable
{
public:

    ///Constructor
    Movable();
    ///Move a moveable entity forward
	virtual void moveForward() = 0;
    ///Move a moveable entity backward
	virtual void moveBackward() = 0;
    ///Rotate a moveable entity left
	virtual void rotateLeft() = 0;
    ///Rotate a moveable entity right
	virtual void rotateRight() = 0;
	///Check state of entity to see number of times it has been blocked by another object
	virtual const blocked_status isBlocked() = 0;
	//Change this to return an enum of the blocked direction
	///Set the movement direction of the entity
	virtual void setMovementDirection(const movement_direction Movement_input) = 0;
	///Destructor
	virtual ~Movable() = 0;

protected:
    ///Define the movement speed of a missile entity
    static const int _missileMovementSpeed = 8;
    ///Define the movement speed of a tank entity
    static const int _tankMovementSpeed = 3;
    ///Define the rotation speed of a missile entity
    static const int _missileRotationSpeed = 45;
    ///Define the rotatioin speed of a tank entity
    static const int _tankRotationSpeed = 5;

private:
    /// Arguments to be added upon
};





#endif // MOVEABLE_H_
