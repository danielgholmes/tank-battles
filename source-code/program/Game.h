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
#include "Keyboard.h"

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

	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
    GameStateManager _state_manager;
    TurretManager _turret_manager;

    /// Game runtime data
    GameManagementData _game_management_data;

    SpriteDimensions _game_sprite_dimensions;

    /// Container for all entities on the game world
	std::vector<std::weak_ptr<Deletable>> _world_entities;

    // File name for the map grid text file
    std::string map_grid_filename = "map_grid.txt";

    /// Function used to create base map sprites from a .txt file template
	void setupInitialMap();

	/// Function that reads and saves the map text file data
	void getMapData(std::vector<std::vector<char>>& map_vector, std::ifstream& map_grid_file);

    /// Function that reads the map data and prepares placement of entities
	void readMapData(const std::vector<std::vector<char>>& map_vector);

	/// Checks realtime input of keyboard controls in main game loop
	void checkKeyboardInput(ActionData& action_data_container);

	/// Function thats tells all managers to operate
	void runAllManagers(GameManagementData& game_data_container, std::shared_ptr<Display> display);

	/// Function that will add new entity based on action
	void addNewWorldEntity(GameManagementData& game_data_container);

	/// Helper function for setupInitialMap
	void addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation);

    /// Adds new missile to the game
	void addNewMissile(std::shared_ptr<Deletable> missile_del_sp);

	/// Adds a new mine to the game
	void addNewMine(std::shared_ptr<Deletable> mine_del_sp);

	/// Adds a new turret to the game
	void addNewTurret(float turret_positionX, float turret_postionY, float rotation);

	/// Logic function used to recreate a tank once it has been destroyed
	void manageRespawns(GameManagementData& game_data_container);

    /// Helper function for setupInitialMap
	void createBarrier(int x, int y);


	void addDeletable(std::shared_ptr<Deletable> deletable_sp);
	void addCollidable(std::shared_ptr<Deletable> collidable_sp);
	void addMovable(std::shared_ptr<Deletable> movable_sp);
	void addTrackable(std::shared_ptr<Deletable> trackable_sp);
};
#endif // GAME_H_
