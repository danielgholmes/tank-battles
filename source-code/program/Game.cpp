/**
 * \file 	Game.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Game class
 */

#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

void Game::runWorld(std::shared_ptr<Display> display)
{
    setupInitialMap();

    // initialise objects and variables to be used within the main program loop
	sf::RenderWindow window(sf::VideoMode(1200,675), "Hello");
	window.setFramerateLimit(45); // may need to synchronise things another way later on

	while(display->isOpen()) // main game loop
	{
		_game_management_data.resetActionsInfo();
		display->pollEvents(window);
		checkKeyboardInput(_game_management_data);
		runAllManagers(_game_management_data, display, window);
		addNewWorldEntity(_game_management_data);
		display->drawAndDisplayEverything(window);
	}

	return;
}

void Game::checkKeyboardInput(ActionData& action_data_container)
{
    Keyboard keyboard;

	// input for tank 1
    if (keyboard.isKeyPressed(Left))
    {
    	action_data_container.rotateLeftP1(); // tank 1 rotate left
	}
	if (keyboard.isKeyPressed(Right))
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
	if (keyboard.isKeyPressed(A))
	{
    	action_data_container.rotateLeftP2(); // tank 2 rotate left
	}
	if (keyboard.isKeyPressed(D))
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

void Game::setupInitialMap()
{
	std::ifstream map_grid_file(map_grid_filename);
  	std::vector<std::vector<char>> map_vector;

  	getMapData(map_vector, map_grid_file);
  	readMapData(map_vector);
}

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

void Game::runAllManagers(GameManagementData& game_data_container, std::shared_ptr<Display> display, sf::RenderWindow& _window)
{
    _turret_manager.manage();
    _collision_manager.manage();
	_move_manager.manage(game_data_container);
	_tracking_manager.manage(game_data_container);
	_destruction_manager.manage(game_data_container);
	_state_manager.manage(game_data_container);
	_draw_manager.manage(game_data_container, display, _window);
}

void Game::addNewWorldEntity(GameManagementData& game_data_container)
{
    actions_info actions = game_data_container.giveActionInfo();

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
	else if (actions.change_2 == true)
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

void Game::addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation)
{
	std::shared_ptr<Deletable> new_tank_del_sp(new Tank(tank_positionX, tank_positionY,rotation, player_tank));
    _destruction_manager.addNewEntity(new_tank_del_sp);

    addDeletable(new_tank_del_sp);
    addCollidable(new_tank_del_sp);
    addMovable(new_tank_del_sp);
    addTrackable(new_tank_del_sp);
}

void Game::addNewTurret(float turret_postionX, float turret_positionY, float rotation)
{
    std::shared_ptr<Deletable> new_turret_del_sp(new Turret(turret_postionX, turret_positionY, rotation));
    _destruction_manager.addNewEntity(new_turret_del_sp);

    addDeletable(new_turret_del_sp);
    addCollidable(new_turret_del_sp);
    addTrackable(new_turret_del_sp);
    addTurretable(new_turret_del_sp);
}

void Game::addNewMissile(std::shared_ptr<Deletable> missile_del_sp)
{
    _destruction_manager.addNewEntity(missile_del_sp);

    addDeletable(missile_del_sp);
    addCollidable(missile_del_sp);
    addMovable(missile_del_sp);
}

void Game::addNewMine(std::shared_ptr<Deletable> mine_del_sp)
{
    _destruction_manager.addNewEntity(mine_del_sp);

    addDeletable(mine_del_sp);
    addCollidable(mine_del_sp);
}

void Game::createBarrier(int x, int y)
{
    std::shared_ptr<Deletable> new_barrier_del_sp(new Barrier(x, y, barrier));
    _destruction_manager.addNewEntity(new_barrier_del_sp);

    addDeletable(new_barrier_del_sp);
    addCollidable(new_barrier_del_sp);
}

void Game::addDeletable(std::shared_ptr<Deletable> deletable_sp)
{
    std::weak_ptr<Deletable> deletable_wp = deletable_sp;
    _world_entities.push_back(deletable_wp);
    _draw_manager.addNewEntity(deletable_wp);
}

void Game::addCollidable(std::shared_ptr<Deletable> deletable_sp)
{
    std::weak_ptr<Collidable> collidable_wp = std::dynamic_pointer_cast<Collidable>(deletable_sp);
    _collision_manager.addNewEntity(collidable_wp);
}

void Game::addMovable(std::shared_ptr<Deletable> movable_sp)
{
    std::weak_ptr<Movable> movable_wp = std::dynamic_pointer_cast<Movable>(movable_sp);
    _move_manager.addNewEntity(movable_wp);
}

void Game::addTrackable(std::shared_ptr<Deletable> trackable_sp)
{
	std::weak_ptr<Trackable> trackable_wp = std::dynamic_pointer_cast<Trackable>(trackable_sp);
	_tracking_manager.addNewEntity(trackable_wp);
}

void Game::addTurretable(std::shared_ptr<Deletable> turret_sp)
{
    std::weak_ptr<Turret> turret_wp = std::dynamic_pointer_cast<Turret>(turret_sp);
	_turret_manager.addNewEntity(turret_wp);
}

Game::~Game()
{

}
