/**
 * \file 	SpriteDimensions.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that holds all sprite dimensions for the game
 */


#include "SpriteDimensions.h"


SpriteDimensions::SpriteDimensions():
    map_sprite_x(5000),
    map_sprite_y(5000),
    tank_sprite_x(50),
    tank_sprite_y(50),
    missile_sprite_x(12),
    missile_sprite_y(12),
    barrier_sprite_x(100),
    barrier_sprite_y(100),
    mine_sprite_x(20),
    mine_sprite_y(20),
    mine_creation_offset(80),
    missile_creation_offset(20)

    {}

SpriteDimensions::~SpriteDimensions()
{
    //Think of something here
}
