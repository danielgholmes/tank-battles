/**
 * \class  Trackable
 * \file   Trackable.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   4 September 2014
 * \brief  Parent class for all objects capable of being 'Tracked' within the game world
 *
 */

#ifndef TRACKABLE_H_
#define TRACKABLE_H_

//Forward Declarations

//Includes
#include "Deletable.h"
#include "SFML/Graphics.hpp"

class Trackable: virtual public Deletable
{
public:
    ///Constructor
    Trackable();
    ///Get the current x co-ordinates of Trackable object
    virtual const float getPositionX() = 0;
    ///Get the current y co-ordinates of Trackable object
    virtual const float getPositionY() = 0;
    ///Get the current orientation of Trackable object
    virtual const float getOrientation() = 0;
    ///Get the bounding box relevant for line-of-fire detection
    virtual const rect_corners& getTrackingBoundingBox() = 0;
    ///Destructor
    virtual ~Trackable() = 0;

private:

};

#endif
