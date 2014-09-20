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
    tank_sprite_x(130),
    tank_sprite_y(80),
    missile_sprite_x(20),
    missile_sprite_y(20),
    barrier_sprite_x(200),
    barrier_sprite_y(200),
    mine_sprite_x(80),
    mine_sprite_y(80),
    mine_creation_offset(60),
    missile_creation_offset(20)

    {}

SpriteDimensions::~SpriteDimensions()
{
    //Think of something here
}
