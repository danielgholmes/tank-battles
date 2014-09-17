/**
 * \class  Orientation
 * \file   Orientation.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   17 September 2014
 * \brief  Data class for all game entity's orientation
 */

 #include "Structures.h"

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

class Orientation
{
public:
	///Constructor that initialises all data members of the class
	Orientation(float origin_x, float origin_y, float width, float height, float rotation);
	///Returns the entity origin x value
	const float getOriginX();
	///Returns the entity origin y value
	const float getOriginY();
	///Returns the entity width
	const float getWidth();
	///Returns the entity height
	const float getHeight();
	///Returns the entity rotation
	const float getRotation();
	///Move the entity by a distance
	void move(float movement_in_x, float movement_in_y);
	///Rotate the entity by a supplied angle
    void rotate(float angle);
    ///Retrieve Rectangular co-ordinates for collision detection
    rect_corners& getGlobalBounds();

	~Orientation();

private:
	float _origin_x;
	float _origin_y;
	float _width;
	float _height;
	float _rotation;
	rect_corners _collison_box;
};
#endif // ORIENTATION_H_
