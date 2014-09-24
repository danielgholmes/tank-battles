/**
 * \file 	Structures.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that performs game wolrd functions
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

//Includes
#include "SFML/Graphics.hpp"

enum entity_type {
	p1_tank = 1,
	p2_tank,
	p1_missile,
	p2_missile,
	p1_mine,
	p2_mine,
	barrier
	};

enum player_action {
	forward = 1,
	reverse,
	rotate_left,
	rotate_right,
	fire_missile,
	lay_mine,
	do_nothing
	};

/// player_action is an enum of the possible actions that the tank can take
struct actions_info
{   // 1 and 2 correspond to tanks 1 and 2
	bool change_1; // manager needs to know if there was any change
	bool change_2;
	player_action move_1; // info for the move manager
	player_action move_2;
	player_action attack_1; // attack is either plant mine or fire missile
	player_action attack_2; // perhaps need a better name
};


struct textures
{
	sf::Texture tank_1; // player 1 and 2 will have different tank textures
	sf::Texture tank_2;
	sf::Texture missile;
	sf::Texture mine;
	sf::Texture barrier;
	sf::Texture map;
};

struct coordinate
{
    float x;
    float y;
};

///Contains x and y corners of a rectangle, used in the algorithm for collision detection
struct rect_corners
{
    coordinate upper_left;
    coordinate upper_right;
    coordinate lower_left;
    coordinate lower_right;
};

///Contains information about the game state
struct game_state_info
{
    bool finished;
    double runtime;
    // int player1_score;
    // int player2_score;
};


#endif

