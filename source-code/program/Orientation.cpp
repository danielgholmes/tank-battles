//! Implementation for Orientation class
/*! As a means to remove SFML from being tightly coupled to each model entity within
    the game, the Orientation class holds the x_pos, y_pos and rotation of each entity as
    a compositon of entity classes. Orientiaion is also responsible for producing the bounding
    boxes of entites used for collision detection.
    \file   Orientation.cpp
    \author Daniel Holmes & Jonathan Gerrand
    \version 2.0
    \date   17 September 2014
 */

#include "Orientation.h"
#include <cmath>
#define PI          3.141592653589793238462643383279502884L

//! Constructor for Orientation class
/*! Default constructor for the Orientation class
    \param origin_x :: The initial x-coordinate of the orientation object
    \param origin_y :: The initial y-coordinate of the orientation object
    \param width :: The sprite width which the orientation object will mimic
    \param height :: The sprite height which the orientation object will mimic
    \param rotation :: The initial rotation held by the orientation object
    \param controllable :: This destinguishes what type of bounding box the orientation class should create
*/
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

//! Get the current x-coordinate of the orientation object
/*! Simple getter method with exception handling to prevent an invalid state from occuring
    \return const float
*/
const float Orientation::getOriginX()
{
    if (_origin_x < -100) throw InvalidStateOfCoordinates();
	return _origin_x;
}

//! Get the current y-coordinate of the orientation object
/*! Simple getter method with exception handling to prevent an invalid state from occuring
    \return const float
*/
const float Orientation::getOriginY()
{
    if (_origin_y < -100) throw InvalidStateOfCoordinates();
	return _origin_y;
}

//! Get the current width of the orientation object
/*! Simple getter method used during drawing methods of the DrawManager
    to allow for easy data extraction
    \return  const float
*/
const float Orientation::getWidth()
{
	return _width;
}

//! Get the current height of the orientation object
/*! Simple getter method used during drawing methods of the DrawManager
    to allow for easy data extraction
    \return  const float
*/
const float Orientation::getHeight()
{
	return _height;
}

//! Get the current rotation of the orientation object.
/*! Simple getter method used during drawing methods of the DrawManager
    to allow for easy data extraction.
    \return  const float
*/
const float Orientation::getRotation()
{
	return _rotation;
}

//! Set a new value for an orientation objects width.
/*! Simple setter method used to extract the width of an orientation.
    object
    \param width :: The new width value to be assigned to the orientation object
*/
void Orientation::setWidth(const float width)
{
    _width = width;
}

//! Set a new value for an orientation objects height.
/*! Simple setter method used to extract the height of an orientation
    object.
    \param height :: The new height value to be assigned to the orientation object
    \return  const float
*/
void Orientation::setHeight(const float height)
{
    _height = height;
}

//! Move the orientation object positively by (x,y) units.
/*! This method replaces that of SF::RectInt32.move(). It takes in
    cartestian parameters and moves the object relative to its currect position
    in the positive direction specified.
    \param movement_in_x :: The movement direction for the x component
    \param movement_in_y :: The movement direction for the y component
*/
void Orientation::move(float movement_in_x, float movement_in_y)
{
    _origin_x += movement_in_x;
    _origin_y += movement_in_y;
}

//! Rotate the orientation object positively by (x) units.
/*! This method replaces that of SF::RectInt32.rotate(). It takes in
    an angular parameters and rotates the object relative to its currect position.
    Conditional logic is implemented here as a means only to manintain class invariance
    in the positive direction specified.
    \param angle :: The rotation in degreees
*/
void Orientation::rotate(float angle)
{
    //Positive revolution
    if ((_rotation+angle) >= 360 )
    {
       _rotation += angle;
       while (_rotation > 360)
       _rotation -= 360;
    }
    //Negative revolution
    else if ((_rotation+angle) < 0)
    {
        _rotation += angle;
        while (_rotation < 0)
        _rotation += 360;
    }
    else
       _rotation += angle;
}

//! Provides the non-axis-aligned bounding box of the orientation entity
/*! The need for an accurate bounding box is cruxial for collision detection.
    This function is responsible for fetching this box.
    \return rect_corners
*/
rect_corners& Orientation::getGlobalBounds()
{
    setGlobalBounds();
    return _collison_box;
}

//! Function used to calculate the axis-aligned (simplified) bounding box of the orientation entity
/*! The bounding box of the entity is calculated by taking its orientation components and extending four
    four verticies outwards from its origin
    \return rect_corners
*/
const rect_corners& Orientation::getAlignedGlobalBounds()
{
    rect_corners temp_box;
    //Bottom-left corner assignment
    temp_box.lower_left.x = (-_width/2) + getRelativeX();
    temp_box.lower_left.y = (-_height/2)+ getRelativeY();

    //Bottom-right corner assignment
    temp_box.lower_right.x = (+_width/2) + getRelativeX();
    temp_box.lower_right.y = (-_height/2)+ getRelativeY();

     //Top-left corner assignment
    temp_box.upper_left.x = (-_width/2) + getRelativeX();
    temp_box.upper_left.y = (+_height/2)+ getRelativeY();

    //Top-right corner assignment
    temp_box.upper_right.x = (+_width/2) + getRelativeX();
    temp_box.upper_right.y = (+_height/2)+ getRelativeY();

    return temp_box;
}

//! Function used to set the direction in which the orientation object is currently moving.
/*! The need to know in which direction an orientation object is traveling is vitally importatnt
    for movable object collision detection. Based upon this value, a different bounding box will
    be produced for the object.
    \param movement_command :: an Enum defining the four cardinal directions
*/
void Orientation::setMoveDirection(const movement_direction movement_command)
{
    _movement_direction = movement_command;
}

//! Class destructor
/*!

*/
Orientation::~Orientation()
{
    //Possibly add code
}

//! Function used to calculate the non-axis-aligned (Complex) bounding box of the orientation entity.
/*! The bounding box of the entity is calculated by taking its orientation components and extending four
    four verticies outwards within the bounds of a trigometric relationship from its origin.
    \return rect_corners
*/
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

//! Used to determine the relative/future position of an orientation object.
/*! In order to calculate an accurate collision occuring beforehand, the next value of
    x and y coordinated need to be provided to produce a valid bounding box.
    \return float
*/
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

//! Used to determine the relative/future position of an orientation object.
/*! In order to calculate an accurate collision occuring beforehand, the next value of
    x and y coordinated need to be provided to produce a valid bounding box.
    \return float
*/
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

//! Used to determine the relative/future rotation of an orientation object.
/*! In order to calculate an accurate collision occuring beforehand, the next value of
    the rotation needs to be provided to produce a valid bounding box.
    \return float
*/
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

//! Opperator used for testing purposes of the orientation class
/*! This function is written to allow for comparison of created orientation objects in an
    efficient manner without the DRY principal being violatued.
    \param rhs :: an Orientation object.
    \return bool
*/
bool Orientation::operator==(Orientation& rhs) const
{

    if(_origin_x != rhs.getOriginX()) return false;
    if(_origin_y != rhs.getOriginY()) return false;
    if(_rotation != rhs.getRotation()) return false;
    if(_height != rhs.getHeight()) return false;
    if(_width != rhs.getHeight()) return false;

    return true;
}
