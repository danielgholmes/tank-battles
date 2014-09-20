/**
 * \class  Tank
 * \file   Tank.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Child class for all tank objects
 */


#ifndef TANK_H_
#define TANK_H_

//Forward declarations

//Includes
#include "Movable.h"
#include "Collidable.h"
#include "Trackable.h"
#include "Structures.h"
#include "Orientation.h"
#include "math.h"
#include "SpriteDimensions.h"

//Exception Throws
class InvalidConstructorArguments {};


class Tank: virtual public Movable, virtual public Collidable, public Trackable
{
public:

    ///Default Tank object constructor
    Tank(float positionX, float positionY, float rotation, entity_type tankOwner);
    ///Provided ownership
    virtual const entity_type& getType() const;
    ///Allow the object to be rendered
    virtual void draw();
    ///Forward movement for a tank entity
    virtual void moveForward();
    ///Backward movement for a tank entity
	virtual void moveBackward();
    ///Left rotation for a tank entity
	virtual void rotateLeft();
    ///Right rotation for a tank entity
	virtual void rotateRight();
    ///Provide the bounding box for the tank entity
	virtual const rect_corners& getBoundingBox();
    ///Instruct the tank entity that it cannot move
	virtual void setBlocked();
	///Instruct the tank entity that it can move
	virtual void setUnblocked();
    ///Instruct the tank entity that it has collided with another object
	virtual void setCollided();
	///Determine the blocked state of the tank entity
	virtual const bool isBlocked();
    ///Boolean state of the tank entity's life
	virtual bool const isDeleted();
	///Get the current x co-ordinate of Trackable object
    virtual const float getPositionX();
    ///Get the current y co-ordinate of Trackable object
    virtual const float getPositionY();
    ///Get the current orientation of Trackable object
    virtual const float getOrientation();
    ///Retrieve the Tank x Position
    virtual const float getDrawPositionX();
    ///Retrieve the Tank y Position
    virtual const float getDrawPositionY();
    ///Recieve the Tank rotation
    virtual const float getDrawRotation();
	///Tank object destructor
    virtual ~Tank();

private:

    ///Movability of the Tank entity: 1 for blocked, 0 for free
    bool _blockedStatus;
    ///Collision state of the Tank Entity: 1 for collided, 0 for not
    bool _collidedStatus;
    ///The angle of rotation for the Tank entity
    float _rotation;
    ///SFML co-ordinate system for the Tank
    Orientation _tank;
    ///Enumeration type defining the tank
    entity_type _type;
    ///Tank Sprite Dimensions
    SpriteDimensions _sprite_dimensions;
};

#endif // TANK_H_
