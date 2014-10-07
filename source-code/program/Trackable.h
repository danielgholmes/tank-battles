//! An Abstract-based class forming an interface for all Trackable objects within the game
/*! This class is used as an interfacing template by all objects which are capable of
    being Tracked. Trackable classes are handled by the taracking manager
    who has access to all member functions within this class interface.
    \class      Trackable
    \file       Trackable.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       4 September 2014
 */

#ifndef TRACKABLE_H_
#define TRACKABLE_H_
//includes
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
