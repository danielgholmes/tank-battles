//! Implementation for Game class.
/*! This class is responsible for running the main game world. This 
    includes the main game loop. All managers exist and are run
    within this class. It mostly contains private member functions.
    \file       Game.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/


#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

//! Game object constructor.
/*! All private class objects are initialised here, including all the managers.
*/
Game::Game():
    _game_sprite_dimensions(),
    _game_management_data()
{
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
	GameStateManager _state_manager;
	TurretManager _turret_manager;
}

//! Main program loop
/*! The game begins running within this function. Once the initial map is set up the
    main game loop begins. Firstly, thsi function checks if the game window is still open.
    If it is and the game state has not been set as finished, then all main game 
    functions are called. Once the game finishes, the end game screen is displayed
    in an infinite loop. This runs until the game window is closed.
    \param The display object for drawing and displaying all game entities.
*/
void Game::runWorld(std::shared_ptr<Display> display)
{
    setupInitialMap();

	while(display->isOpen()) // main game loop
	{
	    if (!_game_management_data.isGameFinished())
        {
            _game_management_data.resetActionsInfo();
            display->pollEvents();
            checkKeyboardInput(_game_management_data);
            runAllManagers(_game_management_data, display);
            addNewWorldEntity(_game_management_data);
        }
        else
        {
            display->pollEvents();
            display->drawEndScreen();
            display->display();
        }
	}

	return;
}

//! Checks through all pressed control keys.
/*! The keyboard class serves as an interface with Game.cpp and any other keyboard
    library. Should a different keyboard library be desired, adjustments should be
    made to the keyboard enum as well. The action data is changed based on user input.
    This covers both player 1 and player 2 controls.
    \param Information passed by reference about what actions the player has taken.
*/
void Game::checkKeyboardInput(ActionData& action_data_container)
{
    Keyboard keyboard;

	// input for tank 1
    if (keyboard.isKeyPressed(Right))
    {
    	action_data_container.rotateLeftP1(); // tank 1 rotate left
	}
	if (keyboard.isKeyPressed(Left))
	{
    	action_data_container.rotateRightP1(); // tank 1 rotate right
	}
	if (keyboard.isKeyPressed(Up))
	{
    	action_data_container.moveForwardP1(); // tank 1 move forward
	}
	if (keyboard.isKeyPressed(Down))
	{
    	action_data_container.moveBackwardP1(); // tank 1 move backward
	}
	if (keyboard.isKeyPressed(RAlt))
	{
    	action_data_container.mineLaidP1(); // tank 1 plant mine
	}
	if (keyboard.isKeyPressed(RControl))
	{
    	action_data_container.missileFiredP1(); // tank 1 fire missile
	}

	// input for tank 2
	if (keyboard.isKeyPressed(D))
	{
    	action_data_container.rotateLeftP2(); // tank 2 rotate left
	}
	if (keyboard.isKeyPressed(A))
	{
    	action_data_container.rotateRightP2(); // tank 2 rotate right
	}
	if (keyboard.isKeyPressed(W))
	{
    	action_data_container.moveForwardP2(); // tank 2 move forward
	}
	if (keyboard.isKeyPressed(S))
	{
    	action_data_container.moveBackwardP2(); // tank 2 move backward
	}
	if (keyboard.isKeyPressed(LAlt))
	{
    	action_data_container.mineLaidP2(); // tank 2 plant mine
	}
	if (keyboard.isKeyPressed(LControl))
	{
    	action_data_container.missileFiredP2(); // tank 2 fire missile
	}

	return;
}

//! Sets up the game wolrd map.
/*! Maps are read from a textfile. The textfile name can be changed by changing the
    map_grid_filename string in the header. The map is stored as a vector of a vector
    of chars. This vector is used later on from which the map is drawn. Layout of the
    game world can be adjusted by changing the map grid file. 
*/
void Game::setupInitialMap()
{
	std::ifstream map_grid_file(map_grid_filename);
  	std::vector<std::vector<char>> map_vector;

  	getMapData(map_vector, map_grid_file);
  	readMapData(map_vector);
}

//! Reads map data from text file.
/*! The data is read from a textfile and saved to the vector. The file is read line by
    line and saved to a primary vector. This primary vector is then saved to a secondary
    vector which holds each line or horizontal set of map block. Each symbol corresponds
    to a single game entity.
    \param Vector that contains the map, which is written to here.
    \param Reference to the map file object
*/
void Game::getMapData(std::vector<std::vector<char>>& map_vector, std::ifstream& map_grid_file)
{
    std::vector<char> grid_line;

 	if (map_grid_file.is_open())
  	{
		std::string line;
		while ( getline(map_grid_file,line) )
		{
	  		std::istringstream ss(line);
	  		char symbol;
	  		while (ss >> symbol)
	  		{
				grid_line.push_back(symbol);
	  		}
	  		map_vector.push_back(grid_line);
	  		grid_line.clear();
		}
		map_grid_file.close();
	}
  	else std::cout << "Unable to open map file";
}

//! Reads the map data from the vector.
/*! The map data is read from the vector and a game entity's position is set
    accordingly. Any other entities that wish to be added should have a unique
    symbol that is included in the map. If many symbols are needed then a vector of
    symbols may be used.
    \param Map vector is read only.
*/
void Game::readMapData(const std::vector<std::vector<char>>& map_vector)
{
    for (int i = 0; i < map_vector.size(); i++)
  	{
  	    auto temp_vector = map_vector[i];
  		for (int j = 0; j < temp_vector.size(); j++)
  		{
  		    switch(temp_vector[j])
  		    {
            case '#':
                createBarrier(j*_game_sprite_dimensions.barrier_sprite_x, i*_game_sprite_dimensions.barrier_sprite_y);
                break;

            case '1':
                _player1_startX = j*_game_sprite_dimensions.barrier_sprite_x;
                _player1_startY = i*_game_sprite_dimensions.barrier_sprite_y;
                addNewTank(p1_tank, _player1_startX, _player1_startY, 0);
                break;

            case '2':
                _player2_startX = j*_game_sprite_dimensions.barrier_sprite_x;
                _player2_startY = i*_game_sprite_dimensions.barrier_sprite_y;
                addNewTank(p2_tank, _player2_startX, _player2_startY, 180);
                break;

            case 'T':
                _turret_startX = j*_game_sprite_dimensions.turret_sprite_x;
                _turret_startY = i*_game_sprite_dimensions.turret_sprite_y;
                addNewTurret(_turret_startX, _turret_startY, 0);
                break;
  		    }
  		}
  	}
}

//! All managers manage.
/*! Any new manager added should be added here. Note that the only manager that has access to the 
    display is the draw manager.
    \param Tempory game data required by the managers.
    \param Display object required by the draw manager.
*/
void Game::runAllManagers(GameManagementData& game_data_container, std::shared_ptr<Display> display)
{
    _turret_manager.manage();
    _collision_manager.manage();
	_move_manager.manage(game_data_container);
	_tracking_manager.manage(game_data_container);
	_destruction_manager.manage(game_data_container);
	_state_manager.manage(game_data_container);
	_draw_manager.manage(game_data_container, display);
}

//! Any new game entity is added here.
/*! This also includes respawns of tanks that have been destroyed. This function
    checks all actions that a user has executed and creates a new entity accordinly.
    For example, firing a missile or laying a tank would cause a new entity to be created.
    This function requires a lot of refactoring as it is too long and there are repetitions
    in several instances.
    \param Data about what is happening at this point in the game.
*/
void Game::addNewWorldEntity(GameManagementData& game_data_container)
{
    actions_info actions = game_data_container.giveActionInfo();

    manageRespawns(game_data_container);

	//Offset for creating a missile
	const float missile_offset = _game_sprite_dimensions.tank_sprite_y/2 + _game_sprite_dimensions.missile_creation_offset;

	//Offset for creating a mine
    const float mine_offset = _game_sprite_dimensions.tank_sprite_y/2 + _game_sprite_dimensions.mine_creation_offset;

    if (actions.turret_fire)
    {
        auto turret_xPos_vec = _tracking_manager.getTurretPositionsX();
        auto turret_yPos_vec = _tracking_manager.getTurretPositionsY();
        auto turret_rotation_vec = _tracking_manager.getTurretRotations();

        for(int i = 0; i!= turret_xPos_vec.size(); i++)
        {
            const float tur_x_component = cos((turret_rotation_vec[i]*PI)/180);
            const float tur_y_component = sin((turret_rotation_vec[i]*PI)/180);

            std::shared_ptr<Deletable> tur_missile_del_sp(new Missile(turret_xPos_vec[i] + tur_x_component*missile_offset,
                                                                    turret_yPos_vec[i] + tur_y_component*missile_offset,
                                                                    turret_rotation_vec[i], turret_missile));
            addNewMissile(tur_missile_del_sp);
        }
        game_data_container.resetTurretFire();
    }

	if (actions.change_1 == true)
	{
        const float p1_x_component = cos((_tracking_manager.getP1Rotation()*PI)/180);
        const float p1_y_component = sin((_tracking_manager.getP1Rotation()*PI)/180);

		if (actions.attack_1 == fire_missile)
		{	// will use addNewMissile
		    std::shared_ptr<Deletable> p1_missile_del_sp(new Missile(_tracking_manager.getP1PositionX() + p1_x_component*missile_offset,
                                                                    _tracking_manager.getP1PositionY() + p1_y_component*missile_offset,
                                                                    _tracking_manager.getP1Rotation(), p1_missile));
            addNewMissile(p1_missile_del_sp);
		}

        if (actions.attack_1 == lay_mine)
		{	// will use addNewMine
			std::shared_ptr<Deletable> p1_mine_del_sp(new Mine(_tracking_manager.getP1PositionX() - p1_x_component*mine_offset,
                                                               _tracking_manager.getP1PositionY() - p1_y_component*mine_offset,
                                                               p1_mine));
            addNewMine(p1_mine_del_sp);
		}
	}

	if (actions.change_2 == true)

	{
        const float p2_x_component = cos((_tracking_manager.getP2Rotation()*PI)/180);
        const float p2_y_component = sin((_tracking_manager.getP2Rotation()*PI)/180);

		if (actions.attack_2 == fire_missile)
		{	// will use addNewMissile
			std::shared_ptr<Deletable> p2_missile_del_sp(new Missile(_tracking_manager.getP2PositionX() + p2_x_component*missile_offset,
                                                                    _tracking_manager.getP2PositionY() + p2_y_component*missile_offset,
                                                                    _tracking_manager.getP2Rotation(), p2_missile));
            addNewMissile(p2_missile_del_sp);
		}

        if (actions.attack_2 == lay_mine)
		{	// will use addNewMine
			std::shared_ptr<Deletable> p2_mine_del_sp(new Mine(_tracking_manager.getP2PositionX() - p2_x_component*mine_offset,
                                                               _tracking_manager.getP2PositionY() - p2_y_component*mine_offset,
                                                               p2_mine));
            addNewMine(p2_mine_del_sp);
		}
	}
	return;
}

//! Manages when a respawn needs to take place.
/*! Turrets are not respawned in this version. Doing so would reuqired changing GameManagementData.
    Tanks are respawned at their starting positions. No provision is made in this version for
    counteracting spawn raids.
    \param Data the holds information about what tanks need to be respawned 
*/
void Game::manageRespawns(GameManagementData& game_data_container)
{
    if (game_data_container.isP1Respawn())
    {
        addNewTank(p1_tank, _player1_startX, _player1_startY, 0);
        game_data_container.disableP1Respawn();
    }

    if (game_data_container.isP2Respawn())
    {
        addNewTank(p2_tank, _player2_startX, _player2_startY, 180);
        game_data_container.disableP2Respawn();
    }
}

//! Adds a new tank object.
/*! Tank objects are created as Deletables. Each tank is added to the _destruction_manager
    vector. They exists here as shared pointers.
    \param Information about which players tank is being created.
    \param Tank x position
    \param Tank y position
    \param Tanks current rotation angle
*/
void Game::addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation)
{
	std::shared_ptr<Deletable> new_tank_del_sp(new Tank(tank_positionX, tank_positionY,rotation, player_tank));
    _destruction_manager.addNewEntity(new_tank_del_sp);

    addDeletable(new_tank_del_sp);
    addCollidable(new_tank_del_sp);
    addMovable(new_tank_del_sp);
    addTrackable(new_tank_del_sp);
}

//! Adds a new turret object.
/*! Tank objects are created as Deletables. Each turret is added to the _destruction_manager
    vector. They exists here as shared pointers.
    \param Turret x position
    \param Turret y position
    \param Turrets current rotation angle
*/
void Game::addNewTurret(float turret_postionX, float turret_positionY, float rotation)
{
    std::shared_ptr<Deletable> new_turret_del_sp(new Turret(turret_postionX, turret_positionY, rotation));
    _destruction_manager.addNewEntity(new_turret_del_sp);

    addDeletable(new_turret_del_sp);
    addCollidable(new_turret_del_sp);
    addTrackable(new_turret_del_sp);
    addTurretable(new_turret_del_sp);
}

//! Adds a new missile object.
/*! Tank objects are created as Deletables. Each missile is added to the DestructionManager
    vector. They exists here as shared pointers.
    \param Shared pointer that points to the missile object
*/
void Game::addNewMissile(std::shared_ptr<Deletable> missile_del_sp)
{
    _destruction_manager.addNewEntity(missile_del_sp);

    addDeletable(missile_del_sp);
    addCollidable(missile_del_sp);
    addMovable(missile_del_sp);
}

//! Adds a new mine object.
/*! Tank objects are created as Deletables. Each mine is added to the DestructionManager
    vector. They exists here as shared pointers.
    \param Shared pointer that points to the mine object
*/
void Game::addNewMine(std::shared_ptr<Deletable> mine_del_sp)
{
    _destruction_manager.addNewEntity(mine_del_sp);

    addDeletable(mine_del_sp);
    addCollidable(mine_del_sp);
}

//! Adds a new barrier object.
/*! Tank objects are created as Deletables. Each barrier is added to the DestructionManager
    vector. They exists here as shared pointers.
    \param Barrier x pos
    \param Barrier y pos
*/
void Game::createBarrier(int x, int y)
{
    std::shared_ptr<Deletable> new_barrier_del_sp(new Barrier(x, y, barrier));
    _destruction_manager.addNewEntity(new_barrier_del_sp);

    addDeletable(new_barrier_del_sp);
    addCollidable(new_barrier_del_sp);
}

//! Adds entity to deletables vector.
/*! Shared pointers are cast as weak pointers. These are then pushed back to the DrawManager
    vector.
    \param Shared pointer to be cast as weak pointer
*/
void Game::addDeletable(std::shared_ptr<Deletable> deletable_sp)
{
    std::weak_ptr<Deletable> deletable_wp = deletable_sp;
    _world_entities.push_back(deletable_wp);
    _draw_manager.addNewEntity(deletable_wp);
}

//! Adds entity to collidables
/*! Shared pointers are cast as weak pointers. These are then pushed back to the CollisionManager
    vector.
    \param Shared pointer to be cast as weak pointer
*/
void Game::addCollidable(std::shared_ptr<Deletable> deletable_sp)
{
    std::weak_ptr<Collidable> collidable_wp = std::dynamic_pointer_cast<Collidable>(deletable_sp);
    _collision_manager.addNewEntity(collidable_wp);
}

//! Adds entity to movables
/*! Shared pointers are cast as weak pointers. These are then pushed back to the MoveManager
    vector.
    \param Shared pointer to be cast as weak pointer
*/
void Game::addMovable(std::shared_ptr<Deletable> movable_sp)
{
    std::weak_ptr<Movable> movable_wp = std::dynamic_pointer_cast<Movable>(movable_sp);
    _move_manager.addNewEntity(movable_wp);
}

//! Adds entity to trackables
/*! Shared pointers are cast as weak pointers. These are then pushed back to the TrackingManager
    vector.
    \param Shared pointer to be cast as weak pointer
*/
void Game::addTrackable(std::shared_ptr<Deletable> trackable_sp)
{
	std::weak_ptr<Trackable> trackable_wp = std::dynamic_pointer_cast<Trackable>(trackable_sp);
	_tracking_manager.addNewEntity(trackable_wp);
}

//! Adds entity to turrets
/*! Shared pointers are cast as weak pointers. These are then pushed back to the TurretManager
    vector.
    \param Shared pointer to be cast as weak pointer
*/
void Game::addTurretable(std::shared_ptr<Deletable> turret_sp)
{
    std::weak_ptr<Turret> turret_wp = std::dynamic_pointer_cast<Turret>(turret_sp);
	_turret_manager.addNewEntity(turret_wp);
}

Game::~Game()
{

}
