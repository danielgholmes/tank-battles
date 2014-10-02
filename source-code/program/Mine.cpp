/**
 * /file 	Mine.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for Mine class
 */

#include "Mine.h"

///Mine entity constructor
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

///Mine is able to provide its identification
const entity_type& Mine::getType() const
{
    return _type;
}

///Provide the bounding box for the mine entity
const rect_corners& Mine::getBoundingBox()
{
    return _mine.getGlobalBounds();
}

const rect_corners& Mine::getAlignedBoundingBox()
{
    return _mine.getAlignedGlobalBounds();
}

///This function is not used by mine
const int Mine::setBlocked(const blocked_status obstruction_type)
{
    return 1;
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

///Retrieve the Mine x Position
const float Mine::getDrawPositionX()
{
    return _mine.getOriginX();
}

///Retrieve the Mine y Position
const float Mine::getDrawPositionY()
{
    return _mine.getOriginY();
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
