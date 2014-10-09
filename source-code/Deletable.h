//! An Abstract-based class forming an interface for all deletable objects within the game
/*! This class is used as an interfacing template by all objects which are capable of
    being destroyed and drawn. Deletable classes are handled by the both deletion and draw managers
    who have access to all member functions within this class interface.
    \file 	    Deletable.h
    \author 	Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date 	    2 September 2014
 */

#ifndef DELETABLE_H_
#define DELETABLE_H_

//Forward declarations

//Includes
#include "Structures.h"

class Deletable
{
public:

    ///Constructor
	Deletable();
	///Check the death state of an entity
	virtual const bool isDeleted() = 0;
	///Recieve the identification of the created object
    virtual const entity_type& getType() const = 0;
    ///Retrieve the entity's x Position
    virtual const float getDrawPositionX() = 0;
    ///Retrieve the entity's y Position
    virtual const float getDrawPositionY() = 0;
    ///Retrieve the entity's Position
    virtual const float getDrawRotation() = 0;
	///Destructor
	virtual ~Deletable() = 0;

private:

};

#endif
