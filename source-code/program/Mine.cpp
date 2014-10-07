//! Model class for a Mine
/*! Consists of all virtual functions
    \file       TrackingManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#include "Mine.h"

//! Mine entity constructor
/*! Throws exceptions if wrong tank owner of position. Initialises private data members
    \param positionX :: mine's x position
    \param positionY :: mine's y position
    \param mineOwner :: either player 1 or player 2 will own the mine
*/
Mine::Mine(float positionX, float positionY, entity_type mineOwner):
    _mine(positionX,positionY,0.0,0.0,0.0, false),
    _sprite_dimensions()
{
    //Keep Class invariant
    if ((mineOwner != p1_mine) && (mineOwner != p2_mine)) throw InvalidConstructorArgumentsMine();
    if (positionX < 0) throw InvalidConstructorArgumentsMine();
    if (positionY < 0) throw InvalidConstructorArgumentsMine();

    _mine.setWidth(_sprite_dimensions.mine_sprite_x);
    _mine.setHeight(_sprite_dimensions.mine_sprite_y);
    _type = mineOwner;
    _collidedStatus = 0;
}

//! Mine is able to provide its identification
/*! \return const entity_type
*/
const entity_type& Mine::getType() const
{
    return _type;
}

//! Provide the bounding box for the mine entity
/*! \return const rect_corners
*/
const rect_corners& Mine::getBoundingBox()
{
    return _mine.getGlobalBounds();
}

//! Provide the bounding box for the mine entity
/*! \return const rect_corners
*/
const rect_corners& Mine::getAlignedBoundingBox()
{
    return _mine.getAlignedGlobalBounds();
}

//! This function is not used by mine
/*! \return const int
*/
const int Mine::setBlocked(const blocked_status obstruction_type)
{
    return 1;
}

//! This function is not used by mine
/*! 
*/
void Mine::setUnblocked()
{
    //This should be thought about and worked aound
}

//! Set the colllision state of the mine
/*! 
*/
void Mine::setCollided()
{
    _collidedStatus = 1;
}

//! Boolean state of the mine entities 
/*! 
*/
const bool Mine::isDeleted()
{
    return _collidedStatus;
}

//! Retrieve the Mine x Position 
/*! 
*/
const float Mine::getDrawPositionX()
{
    return _mine.getOriginX();
}

//! Retrieve the Mine y Position
/*! 
*/
const float Mine::getDrawPositionY()
{
    return _mine.getOriginY();
}

//! Recieve the Mine rotation
/*! 
*/
const float Mine::getDrawRotation()
{
    return _mine.getRotation();
}

//! Mine object destructor
/*! 
*/
Mine::~Mine()
{
    //This could possibly be added to
}
