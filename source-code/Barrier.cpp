//! Implementation for the Barrier Class
/*! This class provides a base object which can be placed around  and boardering
    the game map. It is currectly indestructible and blocks all objects which interact
    with it.
    \file       Barrier.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
 */

#include "Barrier.h"

//! Constructor for Barrier class.
/*! Default constructor for the Orientation class
    \param positionX :: The initial x-coordinate of the barrier object
    \param positionY :: The initial y-coordinate of the barrier object
    \param barrierTypeSet :: An Enum to provide the barrier a specific classification.

*/
Barrier::Barrier(float positionX, float positionY, entity_type barrierTypeSet):
    _sprite_dimensions(),
    _barrier(positionX,positionY,0,0,0.0,false)
{
    if(positionX < 0) throw InvalidConstructorArgumentsBarrier();
    if(positionY < 0) throw InvalidConstructorArgumentsBarrier();
    if(barrierTypeSet != barrier) throw InvalidConstructorArgumentsBarrier();

    _barrier.setWidth(_sprite_dimensions.barrier_sprite_x);
    _barrier.setHeight(_sprite_dimensions.barrier_sprite_y);
    _type = barrierTypeSet;
}

//! Return the entity type of the Barrier object.
/*! This function is used extensively by managers to distinguish various clustered entities
    from one another.
    \return entity_type :: An Enum representing the barrier type in this instance
*/
const entity_type& Barrier::getType() const
{
    return _type;
}

//! Function used to calculate the non-axis-aligned (complex) bounding box of the Barrier entity
/*! The bounding box of the entity is calculated by extending its origin by the value of of its width
    and height projected along trigonometric co-ordinates
    \return const rect_corners
*/
const rect_corners& Barrier::getBoundingBox()
{
    return _barrier.getGlobalBounds();
}

//! Function used to calculate the axis-aligned (simplified) bounding box of the Barrier entity
/*! The bounding box of the entity is calculated by taking its orientation components and extending four
    four verticies outwards from its origin
    \return const rect_corners
*/
const rect_corners& Barrier::getAlignedBoundingBox()
{
    return _barrier.getAlignedGlobalBounds();
}

//! This function is not currently used by the Barrier class
/*! Scope exists within this fucnction to add damaging effects to barriers as this method
    is called within the collision manager
    \param obstruction_type :: an Enum describing the direction in which the barrier is blocked
    \return const int
*/
const int Barrier::setBlocked(const blocked_status obstruction_type)
{
    return 1;
}

//! This function is not currently used by the Barrier class
/*! Barriers currently cannot become blocked but this function can be implemented
    to add an effect of regenerative barriers which can be broken over time
*/
void Barrier::setUnblocked()
{

}

//! This function is not currently used by the Barrier class
/*! This can be used to assign a fatal state to a barrier after it has recieved critical damage
*/
void Barrier::setCollided()
{

}

//! Function used to delete a barrier
/*! Barriers currently are not deleted within the game main management loop, however this
    function provides the scope to do so with destructable barriers.
    \return const bool
*/
const bool Barrier::isDeleted()
{
    return 0;
}

//! Retrieve the x-coordinate of the barrier object
/*! This function is used by the DrawManager to gather the barriers x draw ordinal information
    \return const float
*/
const float Barrier::getDrawPositionX()
{
    return _barrier.getOriginX();
}

//! Retrieve the y-coordinate of the barrier object
/*! This function is used by the DrawManager to gather the barriers y draw ordinal information
    \return const float
*/
const float Barrier::getDrawPositionY()
{
    return _barrier.getOriginY();
}

//! Retrieve the barrier objects rotation
/*! This function is used by the DrawManager to record the rotation of a barrier sprite it creates
    \return const float
*/
const float Barrier::getDrawRotation()
{
    return _barrier.getRotation();
}

//! Destructor for Barrier
/*! Default destructor
*/
Barrier::~Barrier()
{

}
