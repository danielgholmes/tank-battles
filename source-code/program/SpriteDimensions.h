/**
 * \file 	SpriteDimensions.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that holds all sprite dimensions for the game
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

    const float tank_sprite_y;
    const float missile_sprite_y;
    const float mine_sprite_y;
    const float map_sprite_y;
    const float barrier_sprite_y;

    const float mine_creation_offset;
    const float missile_creation_offset;

    ///Destructor
    ~SpriteDimensions();

};


#endif // SPRITEDIMENSIONS_H_
