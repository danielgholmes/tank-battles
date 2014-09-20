/**
 * \file 	Missile.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Missile class
 */

#include "Missile.h"

///Missile object constructor
Missile::Missile(float positionX, float positionY, float rotation, entity_type missileOwner):

    _rotation(rotation),
    _type(missileOwner),
    _missile(positionX,positionY,0,0,rotation),
    _sprite_dimensions()
{
     //Error input checking
    if (_missile.getOriginX() < 0) throw InvalidConstructorArgumentsMissile();
    if (_missile.getOriginY() < 0) throw InvalidConstructorArgumentsMissile();
    if (_missile.getRotation() < 0) throw InvalidConstructorArgumentsMissile();
    if ((_type != p1_missile) && (_type != p2_missile)) throw InvalidConstructorArgumentsMissile();

    _missile.setWidth(_sprite_dimensions.missile_sprite_x);
    _missile.setHeight(_sprite_dimensions.missile_sprite_y);
    _blockedStatus = 0;
    _collidedStatus = 0;
}

///Return the ownership and type of the Missile entity
const entity_type& Missile::getType() const
{
    return _type;
}


///Forward movement for a missile entity
void Missile::moveForward()
{
    _missile.move(_missileMovementSpeed*cos((_rotation*PI)/180.0),_missileMovementSpeed*sin((_rotation*PI)/180.0));
}

///Backward movement for a missile entity
void Missile::moveBackward()
{
    _missile.move(-_missileMovementSpeed*cos((_rotation*PI)/180.0),-_missileMovementSpeed*sin((_rotation*PI)/180.0));
}

///Left rotation for a missile entity
void Missile::rotateLeft()
{
    _rotation += _missileRotationSpeed;
    _missile.rotate(_missileRotationSpeed);
    _blockedStatus = 0;
}

///Right rotation for a missile entity
void Missile::rotateRight()
{
    _rotation -= _missileRotationSpeed;
    _missile.rotate(-_missileRotationSpeed);
    _blockedStatus = 0;
}

///Provide the bounding box for the missile entity
const rect_corners& Missile::getBoundingBox()
{
    return _missile.getGlobalBounds();
}

///Instruct the missile entity that it cannot move along its trajectory
void Missile::setBlocked()
{
    _blockedStatus = 1;
}

///Instruct the tank entity that it can move
void Missile::setUnblocked()
{
    _blockedStatus = 0;
}

///Instruct the missile entity that it has collided with another object
void Missile::setCollided()
{
    _collidedStatus = 1;
}

///Determine the blocked state of the missile entity
const bool Missile::isBlocked()
{
    return _blockedStatus;
}

///Boolean state of the missile entity's life
const bool Missile::isDeleted()
{
    return _collidedStatus;
}

///Retrieve the Missile x Position
const float Missile::getDrawPositionX()
{
    return _missile.getOriginX();
}

///Retrieve the Missile y Position
const float Missile::getDrawPositionY()
{
    return _missile.getOriginY();
}


///Recieve the Missile rotation
const float Missile::getDrawRotation()
{
    return _missile.getRotation();
}

///Missile object destructor
Missile::~Missile()
{
    //Consider adding something here
}
