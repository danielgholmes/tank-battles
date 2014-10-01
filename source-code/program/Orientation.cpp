/**
 * \file   Orientation.cpp
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   17 September 2014
 * \brief  Data class for all orientation data of entities
 */

#include "Orientation.h"
#include <cmath>

#define PI          3.141592653589793238462643383279502884L


Orientation::Orientation(float origin_x, float origin_y, float width, float height, float rotation, bool controllable):
	_origin_x(origin_x),
	_origin_y(origin_y),
	_width(width),
	_height(height),
	_rotation(rotation),
	_controllable(controllable)
	{
	    _movement_direction = Move;
        setGlobalBounds();
	}

const float Orientation::getOriginX()
{
	return _origin_x;
}

const float Orientation::getOriginY()
{
	return _origin_y;
}

const float Orientation::getWidth()
{
	return _width;
}

const float Orientation::getHeight()
{
	return _height;
}

const float Orientation::getRotation()
{
	return _rotation;
}

void Orientation::setWidth(const float width)
{
    _width = width;
}

void Orientation::setHeight(const float height)
{
    _height = height;
}

void Orientation::move(float movement_in_x, float movement_in_y)
{
    _origin_x += movement_in_x;
    _origin_y += movement_in_y;
}

void Orientation::rotate(float angle)
{
    //Positive revolution
    if ((_rotation+angle) > 360 )
    {
       _rotation += angle;
       _rotation -= 360;
    }
    //Negative revolution
    else if ((_rotation+angle) < 0)
    {
        _rotation += angle;
        _rotation += 360;
    }
    else
       _rotation += angle;
}

rect_corners& Orientation::getGlobalBounds()
{
    setGlobalBounds();
    return _collison_box;
}

void Orientation::setMoveDirection(const movement_direction movement_command)
{
    _movement_direction = movement_command;
}

Orientation::~Orientation()
{
    //Possibly add code
}

void Orientation::setGlobalBounds()
{
    float angle = getRelativeRotation()*(PI/180);

    //Bottom-left corner assignment
    _collison_box.lower_left.x = (-_width/2)*cos(angle) - (-_height/2)*sin(angle) + getRelativeX();
    _collison_box.lower_left.y = (-_width/2)*sin(angle) + (-_height/2)*cos(angle) + getRelativeY();

    //Bottom-right corner assignment
    _collison_box.lower_right.x = (+_width/2)*cos(angle) - (-_height/2)*sin(angle) + getRelativeX();
    _collison_box.lower_right.y = (+_width/2)*sin(angle) + (-_height/2)*cos(angle) + getRelativeY();

     //Top-left corner assignment
    _collison_box.upper_left.x = (-_width/2)*cos(angle) - (+_height/2)*sin(angle) + getRelativeX();
    _collison_box.upper_left.y = (-_width/2)*sin(angle) + (+_height/2)*cos(angle) + getRelativeY();

    //Top-right corner assignment
    _collison_box.upper_right.x = (+_width/2)*cos(angle) - (+_height/2)*sin(angle) + getRelativeX();
    _collison_box.upper_right.y = (+_width/2)*sin(angle) + (+_height/2)*cos(angle) + getRelativeY();

}

float Orientation::getRelativeX() const
{
    float angle = _rotation*(PI/180);
    float returnVal = 0.0;

    if (!_controllable)
        return _origin_x;
    else
    {
        switch(_movement_direction)
        {

        case moveForward:
            returnVal = (_origin_x + TANK_MOVE_SPEED*cos(angle));
            break;

        case moveBackward:
            returnVal = (_origin_x - TANK_MOVE_SPEED*cos(angle));
            break;

        default:
            returnVal = _origin_x;
            break;
        }

        return returnVal;
    }
}

float Orientation::getRelativeY() const
{
    float angle = _rotation*(PI/180);
    float returnVal = 0.0;

    if (!_controllable)
        return _origin_y;
    else
    {
        switch(_movement_direction)
        {

        case moveForward:
            returnVal = (_origin_y + TANK_MOVE_SPEED*sin(angle));
            break;

        case moveBackward:
            returnVal = (_origin_y - TANK_MOVE_SPEED*sin(angle));
            break;

        default:
            returnVal = _origin_y;
            break;
        }

        return returnVal;
    }
}

float Orientation::getRelativeRotation() const
{
    float returnedRotation = 0.0;
    if(!_controllable)
        return _rotation;
    else
    {
        switch (_movement_direction)
        {
        case rotateLeft:
            returnedRotation = _rotation + TANK_ROTATION_SPEED;
            if (returnedRotation > 360)
                returnedRotation -= 360;
            break;

        case rotateRight:
            returnedRotation = _rotation - TANK_ROTATION_SPEED;
            if (returnedRotation < 0)
                returnedRotation += 360;
            break;

        default:
            returnedRotation = _rotation;
        }
    return returnedRotation;
    }
}

bool Orientation::operator==(Orientation& rhs) const
{

    if(_origin_x != rhs.getOriginX()) return false;
    if(_origin_y != rhs.getOriginY()) return false;
    if(_rotation != rhs.getRotation()) return false;
    if(_height != rhs.getHeight()) return false;
    if(_width != rhs.getHeight()) return false;

    return true;
}
