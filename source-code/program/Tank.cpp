//! Implementation of the Tank Class
/*! This class  possesses multiple interfaces for interaction with various managers and
    forms part of the basic model entities
    \file       Tank.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
 */

#include "Tank.h"


//! Constuctor of the Tank Class.
/*! This constructor utilises excetion handling and seeks to ensure that its state is invariant.
    \param positionX :: The initial x-axis to construct the tank on.
    \param positionY :: The initial y-axis to construct the tank on
    \param rotation :: The initial rotation to construct the tank with
    \param tankOwner :: used to set the owner of the tank as either p1 or p2
*/
Tank::Tank(float positionX, float positionY, float rotation, entity_type tankOwner):
    _rotation(rotation),
    _type(tankOwner),
    _tank(positionX,positionY,0,0,rotation, true),
    _sprite_dimensions()
{
    //Error input checking
    if (_tank.getOriginX() < 0) throw InvalidConstructorArgumentsTank();
    if (_tank.getOriginY() < 0) throw InvalidConstructorArgumentsTank();
    if (_tank.getRotation() < 0) throw InvalidConstructorArgumentsTank();
    if ((_type != p1_tank) && (_type != p2_tank)) throw InvalidConstructorArgumentsTank();

    _tank.setWidth(_sprite_dimensions.tank_sprite_x);
    _tank.setHeight(_sprite_dimensions.tank_sprite_y);
    _blockedStatus = unblocked;
    _collidedStatus = 0;
}


//!  Returns the owner of the tank
/*!  This is function is used in many logic instanses where the owner of the
     tank needs to be determined.
     \return entity_type
*/
 const entity_type& Tank::getType() const
 {
     return _type;
 }

//!  Moves the tank forward by a constant value
/*!  This method uses trigonometry to move the tank positively in any 360 degree direction within
     the game world
*/
void Tank::moveForward()
{
    _tank.move(_tankMovementSpeed*cos((_rotation*PI)/180.0), _tankMovementSpeed*sin((_rotation*PI)/180.0));
}


//!  Moves the tank forward by a constant value
/*!  This method uses trigonometry to move the tank negatively in any 360 degree direction within
     the game world
*/
void Tank::moveBackward()
{
    _tank.move(-_tankMovementSpeed*cos((_rotation*PI)/180.0), -_tankMovementSpeed*sin((_rotation*PI)/180.0));
}

//!  Rotates the tank left by a constant value
/*!  This method uses trigonometry to move the tank positively in any degree if rotation
*/
void Tank::rotateLeft()
{
    _rotation += _tankRotationSpeed;
    _tank.rotate(_tankRotationSpeed);
}


//!  Rotates the tank right by a constant value
/*!  This method uses trigonometry to move the tank negatively in any degree if rotation
*/
void Tank::rotateRight()
{
    _rotation -= _tankRotationSpeed;
    _tank.rotate(-_tankRotationSpeed);
}


//!  Retrieves the tanks bounding box
/*!  This function is used in conjunction with collision detection
*/
const rect_corners& Tank::getBoundingBox()
{
    return _tank.getGlobalBounds();
}


//!  Set the movement state of the Tank to be blocked
/*!  This function sets a boolean value and returns an int describing how manay more times it can be blocked
     \param obstruction_type :: this is the direction in which the tank becomes blocked
*/
const int Tank::setBlocked(const blocked_status obstruction_type)
{
    _blockedStatus = obstruction_type;
    //Tank intity can be blocked infinitely.
    return 1;
}

///Instruct the tank entity that it can move
void Tank::setUnblocked()
{
    _blockedStatus = unblocked;
}

///Instruct the tank entity that it has collided with another object
void Tank::setCollided()
{
    _collidedStatus = 1;
}

///Determine the blocked state of the tank entity
const blocked_status Tank::isBlocked()
{
    return _blockedStatus;
}

///Boolean state of the tank entity's life
const bool Tank::isDeleted()
{
    return _collidedStatus;
}

///Get the current x co-ordinates of Trackable object
const float Tank::getPositionX()
{
    return _tank.getOriginX();
}

///Get the current y co-ordinates of Trackable object
const float Tank::getPositionY()
{
    return _tank.getOriginY();
}

///Get the current orientation of Trackable object
const float Tank::getOrientation()
{
    return _tank.getRotation();
}

 ///Get the bounding box relevant for line-of-fire detection
 const rect_corners& Tank::getTrackingBoundingBox()
 {
    return _tank.getGlobalBounds();
 }

 const rect_corners& Tank::getAlignedBoundingBox()
 {
     return _tank.getAlignedGlobalBounds();
 }

///Retrieve the x Tank Position
const float Tank::getDrawPositionX()
{
    return _tank.getOriginX();
}

///Retrieve the y Tank Position
const float Tank::getDrawPositionY()
{
    return _tank.getOriginY();
}

///Recieve the Tank rotation
const float Tank::getDrawRotation()
{
    return _tank.getRotation();
}

///Set the movement direction of the entity
void Tank::setMovementDirection(const movement_direction Movement_input)
{
    _tank.setMoveDirection(Movement_input);
}

///Tank object destructor
Tank::~Tank()
{

}



