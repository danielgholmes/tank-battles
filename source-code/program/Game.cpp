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
	_window_width(800),
	_window_height(600),
    _game_sprite_dimensions()
{
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
	GameStateManager _state_manager;

	loadTextures();
	addNewSprites();

    setupInitialMap();
}

Game::Game(int width, int height):
	_window_width(width),
	_window_height(height),
    _game_sprite_dimensions()
{
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;
	GameStateManager _state_manager;

	loadTextures();
	addNewSprites();

	setupInitialMap();
}

void Game::addNewTank(entity_type player_tank, float tank_positionX, float tank_positionY, float rotation)
{
	std::shared_ptr<Deletable> new_tank_del_sp(new Tank(tank_positionX, tank_positionY,rotation, player_tank));
    _destruction_manager.addNewEntity(new_tank_del_sp);

    //Change to derived classes - Weak pointers
    std::weak_ptr<Deletable> new_tank_del_wp = std::dynamic_pointer_cast<Deletable>(new_tank_del_sp);
    _world_entities.push_back(new_tank_del_wp);
    _draw_manager.addNewEntity(new_tank_del_wp);
    //Cast as Collidable
	std::weak_ptr<Collidable> new_tank_col_wp = std::dynamic_pointer_cast<Collidable>(new_tank_del_sp);
	_collision_manager.addNewEntity(new_tank_col_wp);
    //Cast as Moveable
    std::weak_ptr<Movable> new_tank_mov_wp = std::dynamic_pointer_cast<Movable>(new_tank_del_sp);
	_move_manager.addNewEntity(new_tank_mov_wp);
	//Cast as Trackable
	std::weak_ptr<Trackable> new_tank_track_wp = std::dynamic_pointer_cast<Trackable>(new_tank_del_sp);
	_tracking_manager.addNewEntity(new_tank_track_wp);
}

void Game::addNewTurret(float turret_postionX, float turret_positionY, float rotation)
{
    std::shared_ptr<Deletable> new_turret_del_sp(new Turret(turret_postionX, turret_positionY, rotation));
    _destruction_manager.addNewEntity(new_turret_del_sp);

    //Change to derived classes - Weak pointers
    std::weak_ptr<Deletable> new_turret_del_wp = std::dynamic_pointer_cast<Deletable>(new_turret_del_sp);
    _world_entities.push_back(new_turret_del_wp);
    _draw_manager.addNewEntity(new_turret_del_wp);
    //Cast as Collidable
    std::weak_ptr<Collidable> new_turret_col_wp = std::dynamic_pointer_cast<Collidable>(new_turret_del_sp);
	_collision_manager.addNewEntity(new_turret_col_wp);
    //Cast as Trackable
	std::weak_ptr<Trackable> new_turret_track_wp = std::dynamic_pointer_cast<Trackable>(new_turret_del_sp);
	_tracking_manager.addNewEntity(new_turret_track_wp);
	//Cast as Turret
	std::weak_ptr<Turret> new_turret_tur_wp = std::dynamic_pointer_cast<Turret>(new_turret_del_sp);
	_turret_manager.addNewEntity(new_turret_tur_wp);
}

void Game::setupInitialMap()
{
	std::ifstream map_grid("map_grid.txt");
  	std::vector<std::vector<char>> map_vector;
  	std::vector<char> grid_line;

 	if (map_grid.is_open())
  	{
		std::string line;
		while ( getline(map_grid,line) )
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
		map_grid.close();
	}
  	else std::cout << "Unable to open map file";

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
} //End function

void Game::createBarrier(int x, int y)
{
    std::shared_ptr<Deletable> new_barrier_del_sp(new Barrier(x, y, barrier));
    _destruction_manager.addNewEntity(new_barrier_del_sp);

    //Cast as weak pointer
    std::weak_ptr<Deletable> new_barrier_del_wp = std::dynamic_pointer_cast<Deletable>(new_barrier_del_sp);
    _world_entities.push_back(new_barrier_del_wp);
    _draw_manager.addNewEntity(new_barrier_del_wp);
    //Cast as Collidable
    std::weak_ptr<Collidable> new_barrier_col_wp = std::dynamic_pointer_cast<Collidable>(new_barrier_del_sp);
    _collision_manager.addNewEntity(new_barrier_col_wp);
}

void Game::runWorld()
{
	// initialise objects and variables to be used within the main program loop
	sf::RenderWindow window(sf::VideoMode(_window_width, _window_height), _window_title);
	window.setFramerateLimit(45); // may need to synchronise things another way later on

	actions_info actions; // create the struct
	initialiseActions(actions);

	game_state_info game_state;
	initialiseState(game_state);

	while(window.isOpen())
	{
		initialiseActions(actions);
		pollEvents(window);
		checkKeyboardInput(actions);
		runAllManagers(actions,window,game_state);
		addNewWorldEntity(actions, game_state);
	}

	return;
}

void Game::pollEvents(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        	window.close();

       	/* Include other events here */
    }
}

void Game::initialiseActions(actions_info& actions)
{
	actions.change_1 = false;
	actions.change_2 = false;
	actions.turret_fire = false;
	actions.move_1 = do_nothing;
	actions.move_2 = do_nothing;
	actions.attack_1 = do_nothing;
	actions.attack_2 = do_nothing;
}

void Game::initialiseState(game_state_info& state)
{
    state.finished = false;
    state.player1_respawn = false;
    state.player2_respawn = false;
    state.player1_score = 0;
    state.player2_score = 0;
}

// Note: some logic is in the view
void Game::checkKeyboardInput(actions_info& actions)
{
	// input for tank 1
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
    	actions.change_1 = true; // tank 1 rotate left
    	actions.move_1 = rotate_left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
    	actions.change_1 = true; // tank 1 rotate right
    	actions.move_1 = rotate_right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
    	actions.change_1 = true; // tank 1 move forward
    	actions.move_1 = forward;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
    	actions.change_1 = true; // tank 1 move backward
    	actions.move_1 = reverse;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
	{
    	actions.change_1 = true; // tank 1 plant mine
    	actions.attack_1 = lay_mine;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
    	actions.change_1 = true; // tank 1 fire missile
    	actions.attack_1 = fire_missile;
	}

	// input for tank 2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
    	actions.change_2 = true; // tank 2 rotate left
    	actions.move_2 = rotate_right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
    	actions.change_2 = true; // tank 2 rotate right
    	actions.move_2 = rotate_left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
    	actions.change_2 = true; // tank 2 move forward
    	actions.move_2 = forward;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
    	actions.change_2 = true; // tank 2 move backward
    	actions.move_2 = reverse;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
    	actions.change_2 = true; // tank 2 plant mine
    	actions.attack_2 = lay_mine;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
    	actions.change_2 = true; // tank 2 fire missile
    	actions.attack_2 = fire_missile;
	}

	return;
}

// Note: here is some more logic
void Game::addNewWorldEntity(actions_info& actions, game_state_info& game_state)
{
    if (game_state.player1_respawn == true)
    {
        addNewTank(p1_tank, _player1_startX, _player1_startY, 0);
        game_state.player1_respawn = false;
    }

    if (game_state.player2_respawn == true)
    {
        addNewTank(p2_tank, _player2_startX, _player2_startY, 180);
        game_state.player2_respawn = false;
    }

	//Offset for creating a missile
	const float missile_offset = _game_sprite_dimensions.tank_sprite_y/2 + _game_sprite_dimensions.missile_creation_offset;

	//Offset for creating a mine
    const float mine_offset = _game_sprite_dimensions.tank_sprite_y/2 + _game_sprite_dimensions.mine_creation_offset;

    if (actions.turret_fire == true)
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
            //Add to Deletion Manager - Shared pointer
            _destruction_manager.addNewEntity(tur_missile_del_sp);

            //Add to all other entities - Weak pointer
            std::weak_ptr<Deletable> tur_missile_del_wp = tur_missile_del_sp;
			_world_entities.push_back(tur_missile_del_wp);
            _draw_manager.addNewEntity(tur_missile_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> tur_missile_col_wp = std::dynamic_pointer_cast<Collidable>(tur_missile_del_sp);
			_collision_manager.addNewEntity(tur_missile_col_wp);
            //Cast as Movable (Weak pointer)
            std::weak_ptr<Movable> tur_missile_mov_wp = std::dynamic_pointer_cast<Movable>(tur_missile_del_sp);
			_move_manager.addNewEntity(tur_missile_mov_wp);
        }
        actions.turret_fire = false;
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
            //Add to Deletion Manager - Shared pointer
            _destruction_manager.addNewEntity(p1_missile_del_sp);

            //Add to all other entities - Weak pointer
            std::weak_ptr<Deletable> p1_missile_del_wp = p1_missile_del_sp;
			_world_entities.push_back(p1_missile_del_wp);
            _draw_manager.addNewEntity(p1_missile_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p1_missile_col_wp = std::dynamic_pointer_cast<Collidable>(p1_missile_del_sp);
			_collision_manager.addNewEntity(p1_missile_col_wp);
            //Cast as Movable (Weak pointer)
            std::weak_ptr<Movable> p1_missile_mov_wp = std::dynamic_pointer_cast<Movable>(p1_missile_del_sp);
			_move_manager.addNewEntity(p1_missile_mov_wp);
		}

        if (actions.attack_1 == lay_mine)
		{	// will use addNewMine
			std::shared_ptr<Deletable> p1_mine_del_sp(new Mine(_tracking_manager.getP1PositionX() - p1_x_component*mine_offset,
                                                               _tracking_manager.getP1PositionY() - p1_y_component*mine_offset,
                                                               p1_mine));
            //Add to Deletion Manager - Shared pointer
            _destruction_manager.addNewEntity(p1_mine_del_sp);

            //Add to all other entities - Weak pointer
            std::weak_ptr<Deletable> p1_mine_del_wp = p1_mine_del_sp;
			_world_entities.push_back(p1_mine_del_wp);
			_draw_manager.addNewEntity(p1_mine_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p1_mine_mov_wp = std::dynamic_pointer_cast<Collidable>(p1_mine_del_sp);
            _collision_manager.addNewEntity(p1_mine_mov_wp);
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
            //Add to Destruction Manager - Shared pointer
            _destruction_manager.addNewEntity(p2_missile_del_sp);

			//Convert to weak pointer
			std::weak_ptr<Deletable> p2_missile_del_wp = p2_missile_del_sp;
			_world_entities.push_back(p2_missile_del_wp);
            _draw_manager.addNewEntity(p2_missile_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p2_missile_col_wp = std::dynamic_pointer_cast<Collidable>(p2_missile_del_sp);
			_collision_manager.addNewEntity(p2_missile_col_wp);
            //Cast as Movable (Weak pointer)
            std::weak_ptr<Movable> p2_missile_mov_wp = std::dynamic_pointer_cast<Movable>(p2_missile_del_sp);
			_move_manager.addNewEntity(p2_missile_mov_wp);
		}

        if (actions.attack_2 == lay_mine)
		{	// will use addNewMine
			std::shared_ptr<Deletable> p2_mine_del_sp(new Mine(_tracking_manager.getP2PositionX() - p2_x_component*mine_offset,
                                                               _tracking_manager.getP2PositionY() - p2_y_component*mine_offset,
                                                               p2_mine));
            //Add to Destruction Manager - Shared Pointer
			_destruction_manager.addNewEntity(p2_mine_del_sp);
			//Convert to weak pointer
			std::weak_ptr<Deletable> p2_mine_del_wp = p2_mine_del_sp;
			_world_entities.push_back(p2_mine_del_wp);
			_draw_manager.addNewEntity(p2_mine_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p2_mine_mov_wp = std::dynamic_pointer_cast<Collidable>(p2_mine_del_sp);
            _collision_manager.addNewEntity(p2_mine_mov_wp);
		}
	}

	return;
}


void Game::loadTextures()
{
	_game_textures.tank_1.loadFromFile(_tank1_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.tank_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.tank_2.loadFromFile(_tank2_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.tank_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.missile.loadFromFile(_missile_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.missile_sprite_x,_game_sprite_dimensions.missile_sprite_y));
	_game_textures.mine.loadFromFile(_mine_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.mine_sprite_x,_game_sprite_dimensions.mine_sprite_y ));
	_game_textures.barrier.loadFromFile(_barrier_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.barrier_sprite_x,_game_sprite_dimensions.barrier_sprite_y));
	_game_textures.turret.loadFromFile(_turret_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.turret_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.map.loadFromFile(_map_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.map_sprite_x,_game_sprite_dimensions.map_sprite_y));
	_game_textures.missile_turret.loadFromFile(_missile_turret_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.missile_sprite_x,_game_sprite_dimensions.mine_sprite_y));
}

void Game::runAllManagers(actions_info& actions, sf::RenderWindow& window, game_state_info& game_state)
{
    _turret_manager.manage();
    _collision_manager.manage();
	_move_manager.manage(actions);
	_tracking_manager.manage(actions);
	_destruction_manager.manage(game_state);
	_state_manager.manage(game_state, actions);
	_draw_manager.manage(_sprites, window, game_state);
}

void Game::addNewSprites()
{
    //Create P_1 Tank Sprite
    std::shared_ptr<sf::Sprite> TankOne_sp(new(sf::Sprite));
    TankOne_sp->setTexture(_game_textures.tank_1);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_tank,TankOne_sp));

    //Create P_2 Tank Sprite
    std::shared_ptr<sf::Sprite> TankTwo_sp(new(sf::Sprite));
    TankTwo_sp->setTexture(_game_textures.tank_2);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_tank,TankTwo_sp));

    //Create Barrier Sprite
    std::shared_ptr<sf::Sprite> Barrier_sp(new(sf::Sprite));
    Barrier_sp->setTexture(_game_textures.barrier);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(barrier,Barrier_sp));

    //Create P_1 Missile Sprite
    std::shared_ptr<sf::Sprite> MissileOne_sp(new(sf::Sprite));
    MissileOne_sp->setTexture(_game_textures.missile);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_missile,MissileOne_sp));

    //Create P_2 Missile Sprite
    std::shared_ptr<sf::Sprite> MissileTwo_sp(new(sf::Sprite));
    MissileTwo_sp->setTexture(_game_textures.missile);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_missile,MissileTwo_sp));

    //Create P_1 Mine Sprite
    std::shared_ptr<sf::Sprite> MineOne_sp(new(sf::Sprite));
    MineOne_sp->setTexture(_game_textures.mine);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_mine,MineOne_sp));

    //Create P_2 Mine Sprite
    std::shared_ptr<sf::Sprite> MineTwo_sp(new(sf::Sprite));
    MineTwo_sp->setTexture(_game_textures.mine);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_mine,MineTwo_sp));

    //Create Turret Sprite
    std::shared_ptr<sf::Sprite> Turret_sp(new(sf::Sprite));
    Turret_sp->setTexture(_game_textures.turret);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(turret,Turret_sp));

    //Create Turret Sprite
    std::shared_ptr<sf::Sprite> Turret_missile_sp(new(sf::Sprite));
    Turret_missile_sp->setTexture(_game_textures.missile_turret);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(turret_missile,Turret_missile_sp));

}

Game::~Game()
{

}

