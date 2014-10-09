//! Keeps all structs in a single file.
/*! \file       Structures.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
    \brief      Description of StopWatch class
*/

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

//Includes
#include "SFML/Graphics.hpp"

#define MISSILE_MOVE_SPEED 12
#define TANK_MOVE_SPEED 10
#define MISSILE_ROTATION_SPEED 45
#define TANK_ROTATION_SPEED 5

/// The different types of game entities
enum entity_type {
	p1_tank = 1,
	p2_tank,
	p1_missile,
	p2_missile,
	turret_missile,
	p1_mine,
	p2_mine,
	barrier,
	turret
	};

/// The defferent actions that a player can do
enum player_action {
	forward = 1,
	reverse,
	rotate_left,
	rotate_right,
	fire_missile,
	lay_mine,
	do_nothing
	};

/// Player number
enum player_number {
    p1 =1,
    p2
};

/// Blocked status for different orientations
enum blocked_status
{
    blocked = 1,
    blocked_vertically,
    blocked_horizontally,
    unblocked
};

/// player_action is an enum of the possible actions that the tank can take
struct actions_info
{   // 1 and 2 correspond to tanks 1 and 2
	bool change_1; // manager needs to know if there was any change
	bool change_2;
	bool turret_fire; //State maintained by Tracking manager
	player_action move_1; // info for the move manager
	player_action move_2;
	player_action attack_1; // attack is either plant mine or fire missile
	player_action attack_2; // perhaps need a better name
};

/// All testures in the game
struct textures
{
	sf::Texture tank_1; // player 1 and 2 will have different tank textures
	sf::Texture tank_2;
	sf::Texture missile;
	sf::Texture mine;
	sf::Texture barrier;
	sf::Texture map;
	sf::Texture turret;
	sf::Texture turret_missile;
    sf::Texture end_screen;
};

/// Basic Cartesian coordinate
struct coordinate
{
    float x;
    float y;
};

/// Contains x and y corners of a rectangle, used in the algorithm for collision detection
struct rect_corners
{
    coordinate upper_left;
    coordinate upper_right;
    coordinate lower_left;
    coordinate lower_right;
};

/// Contains information about the game state
struct game_state_info
{
    bool finished;
    double runtime;
    int player1_score;
    int player2_score;
    bool player1_respawn;
    bool player2_respawn;
};

/// Used to define the controlled movement of the player
enum movement_direction
{
    moveForward =1,
    moveBackward,
    rotateLeft,
    rotateRight,
    Move
};

/// Used for passing information from draw manager to display
struct sprite_draw_info
{
    coordinate origin;
    coordinate draw_pos;
    float rotation;
};

/// Holds the strings that will be drawn into text
struct draw_strings
{
    std::string game_time;
    std::string p1_score;
    std::string p2_score;
};

// used for keyboard input in game and keyboard classes
enum gameplay_keys
{
    Left = 1,
    Right,
    Up,
    Down,
    RAlt,
    RControl,
    A,
    D,
    W,
    S,
    LAlt,
    LControl
};


#endif

