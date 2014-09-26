/**
 * \class  Movable
 * \file   Moveable.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Base class for all objects capable of 'Moving' within the game world
 *
 */

#ifndef MOVABLE_H_
#define MOVABLE_H_

//Forward Declarations

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
	///Check state of entity to see if it has been blocked by another object
	virtual const bool isBlocked() = 0;
	///Set the movement direction of the entity
	virtual void setMovementDirection(const movement_direction Movement_input) = 0;
	///Destructor
	virtual ~Movable() = 0;

protected:
    ///Define the movement speed of a missile entity
    static const int _missileMovementSpeed = 12;
    ///Define the movement speed of a tank entity
    static const int _tankMovementSpeed = 10;
    ///Define the rotation speed of a missile entity
    static const int _missileRotationSpeed = 45;
    ///Define the rotatioin speed of a tank entity
    static const int _tankRotationSpeed = 5;

private:
    /// Arguments to be added upon
};





#endif // MOVEABLE_H_
