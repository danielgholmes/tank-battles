/**
 * \class  Collidable
 * \file   Collidable.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   4 September 2014
 * \brief  Parent class for all objects capable of 'Colliding' within the game world
 *
 */


#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_

//Forward declarations


//Includes
#include "Deletable.h"

class Collidable: virtual public Deletable
{
public:
    ///Constructor
    Collidable();
    ///Get bounding box of entity
    virtual const rect_corners& getBoundingBox() = 0;
    ///Set blocked state of entity
    virtual void setBlocked() = 0;
    ///Unset the blocked state of the entity
    virtual void setUnblocked() = 0;
    ///Set collision state of entity
    virtual void setCollided() = 0;
    ///Destructor
    virtual ~Collidable() = 0;

private:

};

#endif


