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
	{}

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
