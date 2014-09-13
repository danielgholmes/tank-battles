/**
 * \file 	Missile.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Missile class
 */

#include "Missile.h"

///Missile object constructor
Missile::Missile(sf::Vector2f  position, float rotation, entity_type missileOwner):

    _rotation(rotation),
    _type(missileOwner)
{
    sf::Sprite _missile;
    _missile.setPosition(position),
    _missile.setRotation(rotation),
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
    _missile.move(_missileMovementSpeed*cos(_rotation),_missileMovementSpeed*sin(_rotation));
}

///Backward movement for a missile entity
void Missile::moveBackward()
{
    _missile.move(_missileMovementSpeed*cos(_rotation),_missileMovementSpeed*sin(_rotation));
}

///Left rotation for a missile entity
void Missile::rotateLeft()
{
    _rotation += _missileRotationSpeed;
    _missile.rotate(_missileRotationSpeed);
}

///Right rotation for a missile entity
void Missile::rotateRight()
{
    _rotation -= _missileRotationSpeed;
    _missile.rotate(-_missileRotationSpeed);
}

///Provide the bounding box for the missile entity
const sf::FloatRect& Missile::getBoundingBox() const
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

///Retrieve the Missile Position
const sf::Vector2f& Missile::getDrawPosition()
{
    return _missile.getPosition();
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
