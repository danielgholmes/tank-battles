//! A Composition-based class representing a simple barrier object within the game world
/*! This class provides a base object which can be placed around  and boardering
    the game map. It is currectly indestructible and blocks all objects which interact
    with it.
    \file       Barrier.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
 */

#ifndef BARRIER_H_
#define BARRIER_H_

//Forward declarations

//Includes
#include "Collidable.h"
#include "Structures.h"
#include "Orientation.h"
#include "SpriteDimensions.h"

//Exception Throws
class InvalidConstructorArgumentsBarrier{};

class Barrier: virtual public Collidable
{
public:

    ///Barrier entity constructor
    Barrier(float positionX, float positionY, entity_type barrierTypeSet);
    ///Barrier is able to provide its identification
    virtual const entity_type& getType() const;
    ///Provide the bounding box for the Barrier entity
	virtual const rect_corners& getBoundingBox() ;
    ///Get Axis Aligned bounding box of entity
	virtual const rect_corners& getAlignedBoundingBox();
    ///This function is not used by barrier
	virtual const int setBlocked(const blocked_status obstruction_type);
	///This function is not used by barrier
	virtual void setUnblocked();
    ///This function may be implmented later**
	virtual void setCollided();
    ///Boolean state of the barrier entities life
	virtual const bool isDeleted();
	///Retrieve the Barrier x Position
    virtual const float getDrawPositionX();
    ///Retrieve the Barrier y Position
    virtual const float getDrawPositionY();
    ///Recieve the Barrier rotation
    virtual const float getDrawRotation();
	///Destructor for the Barrrier entity
	virtual ~Barrier();


private:

    ///Co-cordinate system for Barrier entity
    Orientation _barrier;
    ///Enumeration type defining the Barrier
    entity_type _type;
    ///Dimensions of Barrier
    SpriteDimensions _sprite_dimensions;

};

#endif // TANK_H_
