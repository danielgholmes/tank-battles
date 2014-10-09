//! A container class responsible for posssesing all the Sprite dimensions within the game world
/*! The sprite dimensions class is used predominantly as a compositional class and offers the sprite
    dimensions to all managers which need this information.
    \file       SpriteDimensions.h
    \author 	Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date 	    2 September 2014

 */

#ifndef SPRITEDIMENSIONS_H_
#define SPRITEDIMENSIONS_H_


class SpriteDimensions
{
public:

    ///Constructor
    SpriteDimensions();

    const float tank_sprite_x;
    const float missile_sprite_x;
    const float mine_sprite_x;
    const float map_sprite_x;
    const float barrier_sprite_x;
    const float turret_sprite_x;

    const float tank_sprite_y;
    const float missile_sprite_y;
    const float mine_sprite_y;
    const float map_sprite_y;
    const float barrier_sprite_y;
    const float turret_sprite_y;

    const float mine_creation_offset;
    const float missile_creation_offset;

    ///Destructor
    ~SpriteDimensions();

};


#endif // SPRITEDIMENSIONS_H_
