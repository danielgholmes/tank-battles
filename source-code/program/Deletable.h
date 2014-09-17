/**
 * \class   Deletable
 * \file 	Deletable.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Base class for all entities within
 *          the battle-tank world.
 */

#ifndef DELETABLE_H_
#define DELETABLE_H_

//Forward declarations

//Includes
#include "Structures.h"
#include "SFML/Graphics.hpp"

class Deletable
{
public:

    ///Constructor
	Deletable();
	///Check the death state of an entity
	virtual const bool isDeleted() = 0;
	///Recieve the identification of the created object
    virtual const entity_type& getType() const = 0;
    ///Retrieve the entity's Position
    virtual const sf::Vector2f& getDrawPosition() = 0;
    ///Retrieve the entity's Position
    virtual const float getDrawRotation() = 0;
	///Destructor
	virtual ~Deletable() = 0;

private:

};

#endif
