/**
 * \file 	Missile.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Missile class
 */

#include "Missile.h"
#include <cmath>

///Missile object constructor
Missile::Missile(float positionX, float positionY, float rotation, entity_type missileOwner):

    _rotation(rotation),
    _type(missileOwner),
    _missile(positionX,positionY,0,0,rotation, false),
    _sprite_dimensions()
{
    //Error input checking
    if (_missile.getOriginX() < 0) throw InvalidConstructorArgumentsMissile();
    if (_missile.getOriginY() < 0) throw InvalidConstructorArgumentsMissile();
    if (_missile.getRotation() < 0) throw InvalidConstructorArgumentsMissile();
    if ((_type != p1_missile) && (_type != p2_missile) && (_type != turret_missile)) throw InvalidConstructorArgumentsMissile();

    _missile.setWidth(_sprite_dimensions.missile_sprite_x);
    _missile.setHeight(_sprite_dimensions.missile_sprite_y);
    _blockedStatus = unblocked;
    _collidedStatus = 0;
    _rebound_lives = 7;
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
    float rotationFactor = ((abs(_rotation-180)-90)*2);
    _rotation += rotationFactor;
    _missile.rotate(rotationFactor);

}

///Right rotation for a missile entity
void Missile::rotateRight()
{
    float rotationFactor = ((180-_rotation)*2);
    _rotation += rotationFactor;
    _missile.rotate(rotationFactor);

}

///Provide the bounding box for the missile entity
const rect_corners& Missile::getBoundingBox()
{
    return _missile.getGlobalBounds();
}

const rect_corners& Missile::getAlignedBoundingBox()
{
    return _missile.getAlignedGlobalBounds();
}

///Instruct the missile entity that it cannot move along its trajectory
const int Missile::setBlocked(const blocked_status obstruction_type)
{
    _blockedStatus = obstruction_type;
    _rebound_lives -= 1;
    return _rebound_lives;
}

///Instruct the tank entity that it can move
void Missile::setUnblocked()
{
    _blockedStatus = unblocked;
}

///Instruct the missile entity that it has collided with another object
void Missile::setCollided()
{
    _collidedStatus = 1;
}

///Determine the blocked state of the missile entity
const blocked_status Missile::isBlocked()
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

///Set the movement direction of the entity
void Missile::setMovementDirection(const movement_direction Movement_input)
{
    _missile.setMoveDirection(Movement_input);
}

///Missile object destructor
Missile::~Missile()
{
    //Consider adding something here
}
