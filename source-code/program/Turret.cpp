/**
 * \file   Turret.cpp
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Implementation file for Turrent
 */


#include "Turret.h"


Turret::Turret(float positionX, float positionY, float rotation):
    _rotation(rotation),
    _turret(positionX, positionY, 0, 0,rotation,false),
    _type(turret),
    _sprite_dimensions(),
    _rotation_rate(-2)
{
    //Error input checking
    if (_turret.getOriginX() < 0) throw InvalidConstructorArgumentsTurret();
    if (_turret.getOriginY() < 0) throw InvalidConstructorArgumentsTurret();
    if (_turret.getRotation() < 0) throw InvalidConstructorArgumentsTurret();
    if (_type != turret) throw InvalidConstructorArgumentsTurret();

    _turret.setWidth(_sprite_dimensions.turret_sprite_x);
    _turret.setHeight(_sprite_dimensions.turret_sprite_y);
    _collidedStatus = 0;
}

const entity_type& Turret::getType() const
{
    return _type;
}

const bool Turret::isDeleted()
{
    return _collidedStatus;
}

const float Turret::getDrawPositionX()
{
    return _turret.getOriginX();
}

const float Turret::getDrawPositionY()
{
    return _turret.getOriginY();
}

const float Turret::getDrawRotation()
{
    return _turret.getRotation();
}

const rect_corners& Turret::getBoundingBox()
{
    return _turret.getGlobalBounds();
}

const int Turret::setBlocked()
{
    return 1;
}

void Turret::setUnblocked()
{
    //Do nothing here!
}

void Turret::setCollided()
{
    _collidedStatus = 1;
}

const float Turret::getPositionX()
{
    return _turret.getOriginX();
}

const float Turret::getPositionY()
{
    return _turret.getOriginY();
}

const float Turret::getOrientation()
{
    return _turret.getRotation();
}

const rect_corners& Turret::getTrackingBoundingBox()
{
    return _turret.getGlobalBounds();
}

void Turret::rotateTurret()
{
    _turret.rotate(_rotation_rate);
}

Turret::~Turret()
{
    // Can addd some arguments here
}
