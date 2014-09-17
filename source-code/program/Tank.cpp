/**
 * \file 	Tank.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Tank class
 */

#include "Tank.h"

///Default Tank object constructor
Tank::Tank(sf::Vector2f position, float rotation, entity_type tankOwner):
    _rotation(rotation),
    _type(tankOwner)
{
    sf::Sprite _tank;
    _tank.setPosition(position);
    _tank.setRotation(rotation);
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
    _tank.move(_tankMovementSpeed*cos(_rotation), _tankMovementSpeed*sin(_rotation));
}

///Backward movement for a tank entity
void Tank::moveBackward()
{
    _tank.move(-_tankMovementSpeed*cos(_rotation), -_tankMovementSpeed*sin(_rotation));
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
const sf::FloatRect& Tank::getBoundingBox() const
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

///Get the current co-ordinates of Trackable object
const sf::Vector2f& Tank::getPosition()
{
    return _tank.getPosition();
}

///Get the current orientation of Trackable object
const float Tank::getOrientation()
{
    return _tank.getRotation();
}

///Retrieve the Tank Position
const sf::Vector2f& Tank::getDrawPosition()
{
    return _tank.getPosition();
}

///Recieve the Tank rotation
const float Tank::getDrawRotation()
{
    return _tank.getRotation();
}

///Tank object destructor
Tank::~Tank()
{
    //Set arguments
}



