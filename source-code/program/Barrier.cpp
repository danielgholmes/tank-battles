/**
 * /file 	Barrier.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for Barrier class
 */

#include "Barrier.h"

///Barrier entity constructor
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
const rect_corners& Barrier::getBoundingBox()
{
    return _barrier.getGlobalBounds();
}

///This function is not used by barrier
const int Barrier::setBlocked()
{
    return 1;
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

///Retrieve the Barrier x Position
const float Barrier::getDrawPositionX()
{
    return _barrier.getOriginX();
}

///Retrieve the Barrier y Position
const float Barrier::getDrawPositionY()
{
    return _barrier.getOriginY();
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
