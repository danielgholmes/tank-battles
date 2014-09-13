/**
 * /file 	Barrier.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for Barrier class
 */

#include "Barrier.h"

///Barrier entity constructor
Barrier::Barrier(sf::Vector2f position, entity_type barrierTypeSet)
{
    sf::Sprite _barrier;
    _barrier.setPosition(position);
    _type = barrierTypeSet;
}

///Barrier is able to provide its identification
const entity_type& Barrier::getType() const
{
    return _type;
}

///Barrier entity is able to be rendered
void Barrier::draw()
{
    //This code needs to be filled in
}

///Provide the bounding box for the Barrier entity
const sf::FloatRect& Barrier::getBoundingBox() const
{
    return _barrier.getGlobalBounds();
}

///This function is not used by barrier
void Barrier::setBlocked()
{

}

///This function is not used by barrier
void Barrier::setUnblocked()
{

}

///This function may be implmented later**
void Barrier::setCollided()
{

}

///Barriers are currently immortal and hence will always return a false
const bool Barrier::isDeleted()
{
    return 0;
}

///Retrieve the Barrier Position
const sf::Vector2f& Barrier::getDrawPosition()
{
    return _barrier.getPosition();
}

///Recieve the Barrier rotation
const float Barrier::getDrawRotation()
{
    return _barrier.getRotation();
}

///Destructor for the barrier entity
Barrier::~Barrier()
{

}
