/**
 * \class  Barrier
 * \file   Barrier.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Child class for all barrier objects
 */

#ifndef BARRIER_H_
#define BARRIER_H_

//Forward declarations

//Includes
#include "Collidable.h"
#include "Structures.h"
#include "Orientation.h"



class Barrier: virtual public Collidable
{
public:

    ///Barrier entity constructor
    Barrier(float positionX, float positionY, entity_type barrierTypeSet);
    ///Barrier is able to provide its identification
    virtual const entity_type& getType() const;
    ///Barrier entity is able to be rendered
    virtual void draw();
    ///Provide the bounding box for the Barrier entity
	virtual const rect_corners& getBoundingBox() ;
    ///This function is not used by barrier
	virtual void setBlocked();
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

    ///SFML Co-cordinate system for Barrier entity
    Orientation _barrier; //**Needs to change**
    ///Enumeration type defining the Barrier
    entity_type _type;

};

#endif // TANK_H_
