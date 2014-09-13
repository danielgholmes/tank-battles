/**
 * /file 	Mine.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for Mine class
 */

#include "Mine.h"

///Mine entity constructor
Mine::Mine(sf::Vector2f position, entity_type mineOwner)
{
    sf::Sprite _mine;
    _mine.setPosition(position),
    _type = mineOwner;
    _collidedStatus = 0;
}

///Mine is able to provide its identification
const entity_type& Mine::getType() const
{
    return _type;
}

///Provide the bounding box for the mine entity
const sf::FloatRect& Mine::getBoundingBox() const
{
    return _mine.getGlobalBounds();
}

///This function is not used by mine
void Mine::setBlocked()
{
    //This should be thought about and worked around
}

///This function is not used by mine
void Mine::setUnblocked()
{
    //This should be thought about and worked aound
}

///Set the colllision state of the mine
void Mine::setCollided()
{
    _collidedStatus = 1;
}

///Boolean state of the mine entities life
const bool Mine::isDeleted()
{
    return _collidedStatus;
}

///Retrieve the Mine Position
const sf::Vector2f& Mine::getDrawPosition()
{
    return _mine.getPosition();
}

///Recieve the Mine rotation
const float Mine::getDrawRotation()
{
    return _mine.getRotation();
}

///Mine object destructor
Mine::~Mine()
{
    //This could possibly be added to
}
