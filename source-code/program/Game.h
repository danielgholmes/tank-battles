/**
 * \class 	Game
 * \file 	Game.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that performs game wolrd functions
 */


#ifndef GAME_H_
#define GAME_H_

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>

//Structures and enums
#include "Structures.h"

//include all entites
#include "Tank.h"
#include "Missile.h"
#include "Barrier.h"
#include "Mine.h"

//include all managers
#include "MoveManager.h"
#include "CollisionManager.h"
#include "TrackingManager.h"
#include "DrawManager.h"
#include "DestructionManager.h"

class Game
{
public:
	/// Default constructor with default game settings
	Game();

	/// Constuctor with defineable window width and height
	Game(int window_width, int window_height);

	/// Contains the main program loop
	void runWorld();

	/// Destrctor
	~Game();

private:

	int _window_width;
	int _window_height;
	std::string _window_title = "Tank v0.1";

	// const int _num_of_barriers = 2;
	// const int _num_of_tanks = 2; // only 2 for initial testing

	textures _game_textures;

	// Texture file names
	const std::string _tank1_texture_file = "tank1_red.png";
	const std::string _tank2_texture_file = "tank2_green.png";
	const std::string _missile_texture_file = "missile.png";
	const std::string _mine_texture_file = "mine.png";
 	const std::string _barrier_texture_file = "barrier.png";
 	const std::string _map_texture_file = "map.png";
	//const std::string _map_texture_file = "filename";

	/// Container for all entities on the game world
	std::vector<std::shared_ptr<Deletable>> _world_entities;
	/// Container for the sprites that will be drawn
	std::vector<sf::Sprite> _sprites;

    sf::Vector2f _player1_start_pos;
    sf::Vector2f _player2_start_pos;
    sf::Vector2f _barrier_start_pos; // only 1 barrier for now

	// All world managers
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;

	/// Handles all events in main game loop
	void pollEvents(sf::Window& window);

	///
	void initialiseActions(actions_info& actions);

	/// Checks realtime input of keyboard controls in main game loop
	void checkKeyboardInput(actions_info& actions);

	/// Function thats tells all managers to operate
	void runAllManagers(const actions_info& actions);

	/// Function that will add new entity based on action
	void addNewWorldEntity(const actions_info& actions);

	/// Function that adds new sprites to the _sprites vector
	void addNewSprites(const std::string texture_filename, int num_of_sprites);

	/// Function that adds a new tank to the world
	void addNewTank(entity_type player_tank, sf::Vector2f tank_position);

	void addBarriers();

	/// Function that loads all textures into memory
	void loadTextures();

	/// Function that displays all sprites at the end of the main program loop
	void displayAllSprites(sf::Window& window);
};
#endif // GAME_H_
