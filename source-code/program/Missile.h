/**
 * \class  Missile
 * \file   Missile.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Child class for all missile objects
 */

#ifndef MISSILE_H_
#define MISSILE_H_

//Forward Declarations

//Includes
#include "Movable.h"
#include "Collidable.h"
#include "Structures.h"
#include "Orientation.h"
#include "SpriteDimensions.h"

//Exception Throw Classes
class InvalidConstructorArgumentsMissile{};

class Missile: virtual public Movable, virtual public Collidable
{
public:

    ///Missile object constructor
    Missile(float positionX, float positionY, float rotation, entity_type missileOwner);
    ///Return the ownership and type of the Missile entity
    virtual const entity_type& getType() const;
    ///Forward movement for a missile entity
    virtual void moveForward();
    ///Backward movement for a missile entity
	virtual void moveBackward();
    ///Left rotation for a missile entity
	virtual void rotateLeft();
    ///Right rotation for a missile entity
	virtual void rotateRight();
    ///Provide the bounding box for the missile entity
	virtual const rect_corners& getBoundingBox();
    ///Instruct the missile entity that it cannot move along its trajectory
	virtual const int setBlocked();
	///Instruct the missile entity that it can move
	virtual void setUnblocked();
    ///Instruct the missile entity that it has collided with another object
	virtual void setCollided();
	///Determine the blocked state of the missile entity
	virtual const bool isBlocked();
    ///Boolean state of the missile entity's life
	virtual bool const isDeleted();
	///Retrieve the missile x Position
    virtual const float getDrawPositionX();
    ///Retrieve the missile y Position
    virtual const float getDrawPositionY();
    ///Receive the missile rotation
    virtual const float getDrawRotation();
    ///Set the movement direction of the entity
	virtual void setMovementDirection(const movement_direction Movement_input);
	///Missile object destructor
	virtual ~Missile();

private:

    ///Movability of the Missile entity: 1 for blocked, 0 for free
    bool _blockedStatus;
    ///Collision state of the Missile Entity: 1 for collided, 0 for not
    bool _collidedStatus;
    ///The angle of rotation for the Missile entity
    float _rotation;
    ///SFML Co-ordinate system for the Missile
    Orientation _missile;
    ///Enumeration type defining the Missile
    entity_type _type;
    ///Missile Sprite dimensions
    SpriteDimensions _sprite_dimensions;
    ///Defines the number of times the Missile can rebound off barriers
    int _rebound_lives;
};

#endif // TANK_H_
