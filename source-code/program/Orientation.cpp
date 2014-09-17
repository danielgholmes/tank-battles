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
	    //Note that these are all default values and need to be changed
        _collison_box.lower_left.x = 0.0;
        _collison_box.lower_left.y = 0.0;

        _collison_box.lower_right.x = 0.0;
        _collison_box.lower_right.y = 0.0;

        _collison_box.upper_left.x = 0.0;
        _collison_box.upper_left.y = 0.0;

        _collison_box.upper_right.x = 0.0;
        _collison_box.upper_right.y = 0.0;
	}

float Orientation::getOriginX()
{
	return _origin_x;
}

float Orientation::getOriginY()
{
	return _origin_y;
}

float Orientation::getWidth()
{
	return _width;
}

float Orientation::getHeight()
{
	return _height;
}

float Orientation::getRotation()
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
    return _collison_box;
}
