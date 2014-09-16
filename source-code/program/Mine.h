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

class Mine: virtual public Collidable
{
public:

    ///Mine entity constructor
    Mine(sf::Vector2f position, entity_type mineOwner);
    ///Mine is able to provide its identification
    virtual const entity_type& getType() const;
    ///Provide the bounding box for the mine entity
	virtual const sf::FloatRect& getBoundingBox() const;
	///This function is not used by the mine
	virtual void setUnblocked();
    ///This function is not used by mine
	virtual void setBlocked();
    ///Set the colllision state of the mine
	virtual void setCollided();
    ///Boolean state of the mine entities life
	virtual bool const isDeleted();
	///Retrieve the Mine Position
    virtual const sf::Vector2f& getDrawPosition();
    ///Recieve the Mine rotation
    virtual const float getDrawRotation();
	///Mine object destructor
	virtual ~Mine();


private:

    ///SFML Co-cordinate system for Mine entity
    sf::Sprite _mine;
    ///Enumeration type defining the Mine
    entity_type _type;
    ///Collision state of the Mine entity: 1 for collided, 0 for not
    bool _collidedStatus;
};

#endif // TANK_H_
