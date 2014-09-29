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
#include <map>
#include "math.h"

//Structures and enums
#include "Structures.h"
#include "SpriteDimensions.h"

//include all entites
#include "Tank.h"
#include "Missile.h"
#include "Barrier.h"
#include "Mine.h"
#include "Turret.h"

//include all managers
#include "MoveManager.h"
#include "CollisionManager.h"
#include "TrackingManager.h"
#include "DrawManager.h"
#include "DestructionManager.h"
#include "GameStateManager.h"
#include "TurretManager.h"

//Defines
#define PI          3.141592653589793238462643383279502884L

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
	std::string _window_title = "Tank Battles v1.0";

	//Sprite dimensions
    SpriteDimensions _game_sprite_dimensions;

	textures _game_textures;

	float _player1_startX;
	float _player1_startY;
	float _player2_startX;
	float _player2_startY;
	float _turret_startX;
	float _turret_startY;

	//Texture file names
	const std::string _tank1_texture_file = "tank1_red.png";
	const std::string _tank2_texture_file = "tank2_green.png";
	const std::string _missile_texture_file = "missile.png";
	const std::string _mine_texture_file = "mine.png";
 	const std::string _barrier_texture_file = "barrier.png";
 	const std::string _turret_texture_file = "turret.png";
 	const std::string _map_texture_file = "map.png";
 	const std::string _missile_turret_texture_file = "missile_turret.png";


	/// Container for all entities on the game world
	std::vector<std::weak_ptr<Deletable>> _world_entities;
	/// Map container for the sprites that will be drawn
	std::map<entity_type, std::shared_ptr<sf::Sprite>>  _sprites;

	// All world managers
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
    GameStateManager _state_manager;
    TurretManager _turret_manager;

	/// Handles all events in main game loop
	void pollEvents(sf::RenderWindow& window);

	/// Initially populate the actions_info structure
	void initialiseActions(actions_info& actions);

	/// Initially populate the game_state structure
	void initialiseState(game_state_info& game_state);

	/// Checks realtime input of keyboard controls in main game loop
	void checkKeyboardInput(actions_info& actions);

	/// Function thats tells all managers to operate
	void runAllManagers(actions_info& actions, sf::RenderWindow& window, game_state_info& game_state);

	/// Function that will add new entity based on action
	void addNewWorldEntity(actions_info& actions, game_state_info& game_state);

	/// Function which creates the base stamp sprites for the Game
	void addNewSprites();

	/// Function used to create base map sprites from a .txt file template
	void setupInitialMap();

	/// Helper function for setupInitialMap
	void addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation);

	/// Adds a new turret to the game
	void addNewTurret(float turret_positionX, float turret_postionY, float rotation);

    /// Helper function for setupInitialMap
	void createBarrier(int x, int y);

	/// Function that loads all textures into memory
	void loadTextures();

};
#endif // GAME_H_
