//! Model class for a Mine
/*! Consists of all virtual functions
    \file       TrackingManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#ifndef MINE_H_
#define MINE_H_


//Includes
#include "Collidable.h"
#include "Structures.h"
#include "Orientation.h"
#include "SpriteDimensions.h"

class InvalidConstructorArgumentsMine{};

/// Model class for a Mine
class Mine: virtual public Collidable
{
public:

    ///Mine entity constructor
    Mine(float positionX, float positionY, entity_type mineOwner);
    ///Mine is able to provide its identification
    virtual const entity_type& getType() const;
    ///Provide the bounding box for the mine entity
	virtual const rect_corners& getBoundingBox();
	///Get Axis Aligned bounding box of entity
	virtual const rect_corners& getAlignedBoundingBox();
	///This function is not used by the mine
	virtual void setUnblocked();
    ///This function is not used by mine
	virtual const int setBlocked(const blocked_status obstruction_type);
    ///Set the colllision state of the mine
	virtual void setCollided();
    ///Boolean state of the mine entities life
	virtual bool const isDeleted();
	///Retrieve the Mine x Position
    virtual const float getDrawPositionX();
    ///Retrieve the Mine y Position
    virtual const float getDrawPositionY();
    ///Recieve the Mine rotation
    virtual const float getDrawRotation();
	///Mine object destructor
	virtual ~Mine();


private:

    ///Co-cordinate system for Mine entity
    Orientation _mine;
    ///Enumeration type defining the Mine
    entity_type _type;
    ///Collision state of the Mine entity: 1 for collided, 0 for not
    bool _collidedStatus;
    ///Mine sprite dimensions
    SpriteDimensions _sprite_dimensions;
};

#endif // TANK_H_
