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
#include "GameManagementData.h"
#include "GameStateData.h"
#include "ActionData.h"
#include "Display.h"

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
	/// Constuctor with defineable window width and height
	Game();

	/// Contains the main program loop
	void runWorld(std::shared_ptr<Display> display);

	/// Destrctor
	~Game();

private:
	float _player1_startX;
	float _player1_startY;
	float _player2_startX;
	float _player2_startY;
	float _turret_startX;
	float _turret_startY;

	// All world managers
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
    GameStateManager _state_manager;
    TurretManager _turret_manager;

    // Runtime Data
    GameManagementData _game_management_data;

    //Sprite dimensions
    SpriteDimensions _game_sprite_dimensions;

    /// Container for all entities on the game world
	std::vector<std::weak_ptr<Deletable>> _world_entities;

    // File name for the map grid text file
    std::string map_grid_filename = "map_grid.txt";

    /// Function used to create base map sprites from a .txt file template
	void setupInitialMap();

	/// Checks realtime input of keyboard controls in main game loop
	void checkKeyboardInput(ActionData& action_data_container);

	/// Function thats tells all managers to operate
	void runAllManagers(GameManagementData& game_data_container, sf::RenderWindow& window);

	/// Function that will add new entity based on action
	void addNewWorldEntity(GameManagementData& game_data_container);

	/// Helper function for setupInitialMap
	void addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation);

	/// Adds a new turret to the game
	void addNewTurret(float turret_positionX, float turret_postionY, float rotation);

    /// Helper function for setupInitialMap
	void createBarrier(int x, int y);

};
#endif // GAME_H_
