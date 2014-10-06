//! Main class which runs the program loop.
/*! This class is responsible for running the main game world. This 
	includes the main game loop. All managers exist and are run
	within this class. It mostly contains private member functions.
    \file       Game.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
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

/// Used for trigonometric calculations
#define PI          3.141592653589793238462643383279502884L

class Game
{
public:
	Game();
	void runWorld(std::shared_ptr<Display> display);
	~Game();

private:

	/// Player 1 starting x position
	float _player1_startX;
	/// Player 1 starting y position
	float _player1_startY;
	/// Player 2 starting x position
	float _player2_startX;
	/// Player 2 starting y position
	float _player2_startY;
	/// Turret starting x position
	float _turret_startX;
	/// Turret starting y position
	float _turret_startY;

	/// Private object of the MoveManager
	MoveManager _move_manager;
	/// Private object of the CollisionManager
	CollisionManager _collision_manager;
	/// Private object of the TrackingManager
	TrackingManager _tracking_manager;
	/// Private object of the DrawManager
	DrawManager _draw_manager;
	/// Private object of the DestructionManager
	DestructionManager _destruction_manager;
	/// Private object of the GameStateManager
    GameStateManager _state_manager;
    /// Private object of the TurretManager
    TurretManager _turret_manager;

    /// Game runtime data
    GameManagementData _game_management_data;
    /// Dimensions of all game sprites
    SpriteDimensions _game_sprite_dimensions;

    /// Container for all entities on the game world
	std::vector<std::weak_ptr<Deletable>> _world_entities;

    /// File name for the map grid text file
    std::string map_grid_filename = "map_grid.txt";

	void setupInitialMap();
	void getMapData(std::vector<std::vector<char>>& map_vector, std::ifstream& map_grid_file);
	void readMapData(const std::vector<std::vector<char>>& map_vector);

	void checkKeyboardInput(ActionData& action_data_container);
	void runAllManagers(GameManagementData& game_data_container, std::shared_ptr<Display> display);

	void addNewWorldEntity(GameManagementData& game_data_container);
	void addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation);
	void addNewMissile(std::shared_ptr<Deletable> missile_del_sp);
	void addNewMine(std::shared_ptr<Deletable> mine_del_sp);
	void addNewTurret(float turret_positionX, float turret_postionY, float rotation);
	
	void manageRespawns(GameManagementData& game_data_container);
	void createBarrier(int x, int y);

	void addDeletable(std::shared_ptr<Deletable> deletable_sp);
	void addCollidable(std::shared_ptr<Deletable> collidable_sp);
	void addMovable(std::shared_ptr<Deletable> movable_sp);
	void addTrackable(std::shared_ptr<Deletable> trackable_sp);
	void addTurretable(std::shared_ptr<Deletable> trackable_sp);
};
#endif // GAME_H_
