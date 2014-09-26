/**
 * \file 	Tank.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Tank class
 */

#include "Tank.h"

///Default Tank object constructor
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
    _blockedStatus = 0;
    _collidedStatus = 0;
}

///Return the ownership and type of the Tank entity
 const entity_type& Tank::getType() const
 {
     return _type;
 }

///Allow the object to be rendered
void Tank::draw()
{
    //Add code
}

///Forward movement for a tank entity
void Tank::moveForward()
{
    _tank.move(_tankMovementSpeed*cos((_rotation*PI)/180.0), _tankMovementSpeed*sin((_rotation*PI)/180.0));
}

///Backward movement for a tank entity
void Tank::moveBackward()
{
    _tank.move(-_tankMovementSpeed*cos((_rotation*PI)/180.0), -_tankMovementSpeed*sin((_rotation*PI)/180.0));
}

///Left rotation for a tank entity
void Tank::rotateLeft()
{
    _rotation += _tankRotationSpeed;
    _tank.rotate(_tankRotationSpeed);
}

///Right rotation for a tank entity
void Tank::rotateRight()
{
    _rotation -= _tankRotationSpeed;
    _tank.rotate(-_tankRotationSpeed);
}

///Provide the bounding box for the tank entity
const rect_corners& Tank::getBoundingBox()
{
    return _tank.getGlobalBounds();
}

///Instruct the tank entity that it cannot move
void Tank::setBlocked()
{
    _blockedStatus = 1;
}

///Instruct the tank entity that it can move
void Tank::setUnblocked()
{
    _blockedStatus = 0;
}

///Instruct the tank entity that it has collided with another object
void Tank::setCollided()
{
    _collidedStatus = 1;
}

///Determine the blocked state of the tank entity
const bool Tank::isBlocked()
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
    //Set arguments
}



