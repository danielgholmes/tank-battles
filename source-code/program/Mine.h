/**
 * \class  Mine
 * \file   Mine.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Child class for all mine objects
 */

#ifndef MINE_H_
#define MINE_H_


//Includes
#include "Collidable.h"
#include "Structures.h"
#include "Orientation.h"

class Mine: virtual public Collidable
{
public:

    ///Mine entity constructor
    Mine(float positionX, float positionY, entity_type mineOwner);
    ///Mine is able to provide its identification
    virtual const entity_type& getType() const;
    ///Provide the bounding box for the mine entity
	virtual const rect_corners& getBoundingBox();
	///This function is not used by the mine
	virtual void setUnblocked();
    ///This function is not used by mine
	virtual void setBlocked();
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
};

#endif // TANK_H_
