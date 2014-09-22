/**
 * \file 	SpriteDimensions.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that holds all sprite dimensions for the game
 */


#include "SpriteDimensions.h"


SpriteDimensions::SpriteDimensions():
    map_sprite_x(2000),
    map_sprite_y(2000),
    tank_sprite_x(50),
    tank_sprite_y(50),
    missile_sprite_x(5),
    missile_sprite_y(5),
    barrier_sprite_x(50),
    barrier_sprite_y(50),
    mine_sprite_x(40),
    mine_sprite_y(40),
    mine_creation_offset(40),
    missile_creation_offset(20)

    {}

SpriteDimensions::~SpriteDimensions()
{
    //Think of something here
}
