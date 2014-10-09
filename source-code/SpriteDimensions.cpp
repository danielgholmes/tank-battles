//! A container class responsible for posssesing all the Sprite dimensions within the game world
/*! The sprite dimensions class is used predominantly as a compositional class and offers the sprite
    dimensions to all managers which need this information.
    \file       SpriteDimensions.cpp
    \author 	Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date 	    2 September 2014

 */


#include "SpriteDimensions.h"

//! Constructor for Sprite Dimensions
/*! Within the constructor all values are initilised outside of the
    main braces as to allow for the constant values to be initilised
    correctly.

*/
SpriteDimensions::SpriteDimensions():
    map_sprite_x(2000),
    map_sprite_y(2000),
    tank_sprite_x(50),
    tank_sprite_y(50),
    missile_sprite_x(7.5),
    missile_sprite_y(7.5),
    barrier_sprite_x(50),
    barrier_sprite_y(50),
    mine_sprite_x(40),
    mine_sprite_y(40),
    mine_creation_offset(40),
    missile_creation_offset(20),
    turret_sprite_x(50),
    turret_sprite_y(50)

    {}

SpriteDimensions::~SpriteDimensions()
{
}
