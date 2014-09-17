/**
 * \class  Orientation
 * \file   Orientation.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   17 September 2014
 * \brief  Data class for all game entity's orientation
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_ 

class Orientation
{
public:
	///Constructor that initialises all data members of the class
	Orientation(int origin_x, int origin_y, float width, float height, float rotation);
	///Returns the entity origin x value
	int getOriginX();
	///Returns the entity origin y value
	int getOriginY();
	///Returns the entity width
	float getWidth();
	///Returns the entity height
	float getHeight();
	///Returns the entity rotation
	float getRotation();

	~Orientation();

private:
	int _origin_x;
	int _origin_y;
	float _width;
	float _height;
	float _rotation;
};
#endif // ORIENTATION_H_
