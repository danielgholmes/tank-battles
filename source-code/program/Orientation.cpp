/**
 * \file   Orientation.cpp
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   17 September 2014
 * \brief  Data class for all orientation data of entities
 */

#include "Orientation.h"

Orientation::Orientation(float origin_x, float origin_y, float width, float height, float rotation):
	_origin_x(origin_x),
	_origin_y(origin_y),
	_width(width),
	_height(height),
	_rotation(rotation)
	{
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

void Orientation::move(float movement_in_x, float movement_in_y)
{
    _origin_x += movement_in_x;
    _origin_y += movement_in_y;
}

void Orientation::rotate(float angle)
{
    if ((_rotation+angle) > 360 )
    {
       _rotation += angle;
       _rotation -= 360;
    }
    else
       _rotation += angle;
}

rect_corners& Orientation::getGlobalBounds()
{
    setGlobalBounds();
    return _collison_box;
}

Orientation::~Orientation()
{
    //Possibly add code
}

void Orientation::setGlobalBounds()
{
    //Bottom-left corner assignment
    _collison_box.lower_left.x = (_origin_x - _width/2);
    _collison_box.lower_left.y = (_origin_y - _height/2);

    //Bottom-right corner assignment
    _collison_box.lower_right.x = (_origin_x + _width/2);
    _collison_box.lower_right.y = (_origin_y - _height/2);

    //Top-left corner assignment
    _collison_box.upper_left.x = (_origin_x - _width/2);
    _collison_box.upper_left.y = (_origin_y + _height/2);

    //Top-right corner assignment
    _collison_box.upper_right.x = (_origin_x + _width/2);
    _collison_box.upper_right.y = (_origin_y + _height/2);
}

bool Orientation::operator==(const Orientation& rhs) const
{
    auto OrientationObject = rhs;
    if(_origin_x != OrientationObject.getOriginX()) return false;
    if(_origin_y != OrientationObject.getOriginY()) return false;
    if(_rotation != OrientationObject.getRotation()) return false;
    if(_height != OrientationObject.getHeight()) return false;
    if(_width != OrientationObject.getHeight()) return false;
}
