/**
 * \file 	Game.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for Game class
 */

#include "Game.h"

Game::Game():
	_window_width(800),
	_window_height(600)
{
	MoveManager _move_manager;
	CollisionManager _collision_manager;
	TrackingManager _tracking_manager;
	DrawManager _draw_manager;
	DestructionManager _destruction_manager;

   sf::Vector2f _player1_start_pos;
   sf::Vector2f _player2_start_pos;
   sf::Vector2f _barrier_start_pos;

	loadTextures();

	addBarriers(); // only 1 barrier for now
	addNewTank(p1_tank, _player1_start_pos);
	addNewTank(p2_tank, _player2_start_pos);
}

Game::Game(int width, int height):
	_window_width(width),
	_window_height(height)
{}

void Game::addNewTank(entity_type player_tank, sf::Vector2f tank_position)
{
	std::shared_ptr<Deletable> new_tank_del(new Tank(tank_position, 0.0, player_tank));
	_world_entities.push_back(new_tank_del);
    _draw_manager.addNewEntity(new_tank_del);
    _destruction_manager.addNewEntity(new_tank_del);
    //Change to derived classes
    //Cast as Collidable
	std::weak_ptr<Collidable> new_tank_col = std::dynamic_pointer_cast<Collidable>(new_tank_del);
	_collision_manager.addNewEntity(new_tank_col);
    //Cast as Moveable
    std::weak_ptr<Movable> new_tank_mov = std::dynamic_pointer_cast<Movable>(new_tank_del);
	_move_manager.addNewEntity(new_tank_mov);
	//Cast as Trackable
	std::weak_ptr<Trackable> new_tank_track = std::dynamic_pointer_cast<Trackable>(new_tank_del);
	_tracking_manager.addNewEntity(new_tank_track);
}

void Game::addBarriers()
{
    ///Note: I've followed a naming convention here where the type of the smart pointer is used eg: _del, _col etc.
	std::shared_ptr<Deletable> new_barrier_del(new Barrier(_barrier_start_pos, barrier));
	_world_entities.push_back(new_barrier_del);
	_draw_manager.addNewEntity(new_barrier_del);
	//Cast as Collidable
	std::weak_ptr<Collidable> new_barrier_col = std::dynamic_pointer_cast<Collidable>(new_barrier_del);
	_collision_manager.addNewEntity(new_barrier_col);
}

void Game::runWorld()
{
	// initialise objects and variables to be used within the main program loop
	sf::Window window(sf::VideoMode(_window_width, _window_height), _window_title);
	window.setFramerateLimit(60); // may need to synchronise things another way later on

	actions_info actions; // create the struct

	while(window.isOpen())
	{
		initialiseActions(actions);
		pollEvents(window);
		checkKeyboardInput(actions);
		addNewWorldEntity(actions);
		runAllManagers(actions);
		//displayAllSprites(window); //This can only be done in int main() apparently
	}

	return;
}

void Game::pollEvents(sf::Window& window)
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
	actions.move_1 = do_nothing;
	actions.move_2 = do_nothing;
	actions.attack_1 = do_nothing;
	actions.attack_2 = do_nothing;
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
    	actions.move_2 = rotate_left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
    	actions.change_2 = true; // tank 2 rotate right
    	actions.move_2 = rotate_right;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
    	actions.change_2 = true; // tank 2 fire missile
    	actions.attack_2 = fire_missile;
	}

	return;
}

// Note: here is some more logic
void Game::addNewWorldEntity(const actions_info& actions)
{
	// *IMPROVEMENT* the following two if statements are similar
	// could consider adding another function
	if (actions.change_1 == true)
	{
		if (actions.attack_1 == fire_missile)
		{	// will use addNewMissile
		    std::shared_ptr<Deletable> p1_missile_del_sp(new Missile(_tracking_manager.getP1Position(), _tracking_manager.getP1Rotation(), p1_missile));
			_world_entities.push_back(p1_missile_del_sp);
			//Convert to weak pointer
			std::weak_ptr<Deletable> p1_missile_del_wp = p1_missile_del_sp;
			_destruction_manager.addNewEntity(p1_missile_del_wp);
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
			std::shared_ptr<Deletable> p1_mine_del_sp(new Mine(_tracking_manager.getP1Position(), p1_mine));
			_world_entities.push_back(p1_mine_del_sp);
			//Convert to weak pointer
			std::weak_ptr<Deletable> p1_mine_del_wp = p1_mine_del_sp;
			_destruction_manager.addNewEntity(p1_mine_del_wp);
			_draw_manager.addNewEntity(p1_mine_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p1_mine_mov_wp = std::dynamic_pointer_cast<Collidable>(p1_mine_del_sp);
            _collision_manager.addNewEntity(p1_mine_mov_wp);

		}
	}
	else if (actions.change_2 == true)
	{
		if (actions.attack_2 == fire_missile)
		{	// will use addNewMissile
			std::shared_ptr<Deletable> p2_missile_del_sp(new Missile(_tracking_manager.getP2Position(), _tracking_manager.getP1Rotation(), p2_missile));
			_world_entities.push_back(p2_missile_del_sp);
			//Convert to weak pointer
			std::weak_ptr<Deletable> p2_missile_del_wp = p2_missile_del_sp;
			_destruction_manager.addNewEntity(p2_missile_del_wp);
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
			std::shared_ptr<Deletable> p2_mine_del_sp(new Mine(_tracking_manager.getP1Position(), p2_mine));
			_world_entities.push_back(p2_mine_del_sp);
			//Convert to weak pointer
			std::weak_ptr<Deletable> p2_mine_del_wp = p2_mine_del_sp;
			_destruction_manager.addNewEntity(p2_mine_del_wp);
			_draw_manager.addNewEntity(p2_mine_del_wp);
            //Cast as Collidable (Weak pointer)
            std::weak_ptr<Collidable> p2_mine_mov_wp = std::dynamic_pointer_cast<Collidable>(p2_mine_del_sp);
            _collision_manager.addNewEntity(p2_mine_mov_wp);
		}
	}

	return;
}

// void Game::addNewSprites(const std::string texture_filename, int num_of_sprites)
// {
// 	sf::Texture texture;
// 	texture.loadFromFile(texture_filename);
// 	for (int i = 0; i < num_of_sprites; ++i)
// 		_sprites.push_back(sf::Sprite(texture));
// }


void Game::loadTextures()
{
	_game_textures.tank_1.loadFromFile(_tank1_texture_file);
	_game_textures.tank_2.loadFromFile(_tank2_texture_file);
	_game_textures.missile.loadFromFile(_missile_texture_file);
	_game_textures.mine.loadFromFile(_mine_texture_file);
	_game_textures.barrier.loadFromFile(_barrier_texture_file);
	_game_textures.map.loadFromFile(_map_texture_file);
}

void Game::runAllManagers(const actions_info& actions)
{
	_move_manager.manage(actions);
	_collision_manager.manage();
	_tracking_manager.manage();
	_destruction_manager.manage();
	_draw_manager.manage(_sprites, _game_textures);
}

void Game::displayAllSprites(sf::Window& window)
{
//	window.clear();
//	for (auto sprite: _sprites)
//		window.draw(sprite);
//	window.display();
}

