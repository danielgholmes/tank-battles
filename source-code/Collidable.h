//! An Abstract-based class forming an interface for all collidable model objects.
/*! This class is used as an interfacing template by all objects which are capable of
    colliding. Collidable classes are handled by the CollisionManager which has full
    access to all member functions within the class interface
    \file    Collidable.h
    \author  Daniel Holmes & Jonathan Gerrand
    \version 2.0
    \date    4 September 2014
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
    ///Get Axis Aligned bounding box of entity
    virtual const rect_corners& getAlignedBoundingBox() = 0;
    ///Set blocked state of entity
    virtual const int setBlocked(const blocked_status obstruction_type) = 0;
    ///Unset the blocked state of the entity
    virtual void setUnblocked() = 0;
    ///Set collision state of entity
    virtual void setCollided() = 0;
    ///Destructor
    virtual ~Collidable() = 0;

private:

};

#endif


