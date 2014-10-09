//! Implementation for Display class.
/*! This class interfaces with SFML. It receives all information to draw via 
    the DisplayManager. It also contains information such as the file names 
    of all sprite textures.
    \file       Display.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
    
*/


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Display.h"
#include <iostream>

//! Constructor for Display object.
/*! Initialises window dimensions as well as other private objects. The game 
    window title can be changed within the _window constructor. The rest of
    the function makes sure that the main map textures are loaded correctly.
    The text objects for the game are also initialised here.
    \param window_width :: default is set to 800
    \param window_height :: default is set to 600
*/
Display::Display(int window_width, int window_height):
    _window_width(window_width),
    _window_height(window_height),
    _window(sf::VideoMode(_window_width,_window_height), "Tank A Lot"),
    _game_textures(),
    _game_sprite_dimensions()
{
    loadTextures();
    addSprites();

    if (!_map_texture.loadFromFile(_map_texture_file))
        std::cout << "Unable to load Map file!" << std::endl;

    _map_sprite.setTexture(_map_texture);

    if (!_end_map_texture.loadFromFile(_end_texture_file))
        std::cout << "Unable to load Map file!" << std::endl;

    _end_map_sprite.setTexture(_end_map_texture);

    if (!_font_style.loadFromFile(_font_file))
       std::cout << "Unable to load font file!" << std::endl;

    setupText(_game_time_text);
    _game_time_text.setPosition(_game_time_pos,_text_y_allignment);

    setupText(_p1_score_text);
    _p1_score_text.setPosition(_p1_score_pos,_text_y_allignment);

    setupText(_p2_score_text);
    _p2_score_text.setPosition(_p2_score_pos,_text_y_allignment);

	_window.setFramerateLimit(60);

}

//! Checks if the game window is still open.
/*! 
    \return bool
*/
bool Display::isOpen()
{
    if (_window.isOpen())
        return true;
    else return false;
}

//! Clears the display window.
/*! 
*/
void Display::clear()
{
    _window.clear();
}

//! Initialises font properties.
/*! All fonts are the same size, colour and style
    \param text :: the text to be initialised
*/
void Display::setupText(sf::Text& text)
{
    text.setFont(_font_style);
    text.setCharacterSize(_font_size);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
}

//! Loads all textures as Rectangles
/*! Each of the textures are loaded from files. All textures are defined 
    in Structures.h
*/
void Display::loadTextures()
{
    _game_textures.tank_1.loadFromFile(_tank1_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.tank_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.tank_2.loadFromFile(_tank2_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.tank_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.missile.loadFromFile(_missile_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.missile_sprite_x,_game_sprite_dimensions.missile_sprite_y));
	_game_textures.mine.loadFromFile(_mine_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.mine_sprite_x,_game_sprite_dimensions.mine_sprite_y ));
	_game_textures.barrier.loadFromFile(_barrier_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.barrier_sprite_x,_game_sprite_dimensions.barrier_sprite_y));
	_game_textures.turret.loadFromFile(_turret_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.turret_sprite_x,_game_sprite_dimensions.tank_sprite_y));
	_game_textures.map.loadFromFile(_map_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.map_sprite_x,_game_sprite_dimensions.map_sprite_y));
	_game_textures.turret_missile.loadFromFile(_missile_turret_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.missile_sprite_x,_game_sprite_dimensions.missile_sprite_y));
    _game_textures.end_screen.loadFromFile(_end_texture_file, sf::IntRect(0,0,_game_sprite_dimensions.map_sprite_x,_game_sprite_dimensions.map_sprite_y));
}

//! All pointers to SFML sprites are made here.
/*! Each sprite is created and accessed via a shared_ptr. They are saved in
    a map so that they can be referenced when drawn. This means that the 
    number of sprites that exist are equal to the number of unique sprites.
    It is from this map that a copy of the sprite is drawn. Any new sprites
    that will be drawn can be added here.
*/
void Display::addSprites()
{
    //Create P_1 Tank Sprite
    std::shared_ptr<sf::Sprite> tank1_sp(new(sf::Sprite));
    tank1_sp->setTexture(_game_textures.tank_1);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_tank,tank1_sp));

    //Create P_2 Tank Sprite
    std::shared_ptr<sf::Sprite> tank2_sp(new(sf::Sprite));
    tank2_sp->setTexture(_game_textures.tank_2);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_tank,tank2_sp));

    //Create Barrier Sprite
    std::shared_ptr<sf::Sprite> barrier_sp(new(sf::Sprite));
    barrier_sp->setTexture(_game_textures.barrier);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(barrier,barrier_sp));

    //Create P_1 Missile Sprite
    std::shared_ptr<sf::Sprite> missile1_sp(new(sf::Sprite));
    missile1_sp->setTexture(_game_textures.missile);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_missile,missile1_sp));

    //Create P_2 Missile Sprite
    std::shared_ptr<sf::Sprite> missile2_sp(new(sf::Sprite));
    missile2_sp->setTexture(_game_textures.missile);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_missile,missile2_sp));

    //Create P_1 Mine Sprite
    std::shared_ptr<sf::Sprite> mine1_sp(new(sf::Sprite));
    mine1_sp->setTexture(_game_textures.mine);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_mine,mine1_sp));

    //Create P_2 Mine Sprite
    std::shared_ptr<sf::Sprite> mine2_sp(new(sf::Sprite));
    mine2_sp->setTexture(_game_textures.mine);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p2_mine,mine2_sp));

    //Create Turret Sprite
    std::shared_ptr<sf::Sprite> turret_sp(new(sf::Sprite));
    turret_sp->setTexture(_game_textures.turret);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(turret,turret_sp));

    //Create Turret Missile Sprite
    std::shared_ptr<sf::Sprite> turret_missile_sp(new(sf::Sprite));
    turret_missile_sp->setTexture(_game_textures.turret_missile);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(turret_missile,turret_missile_sp));
}

//! Checks SFML window events.
/*! The only event included here is the closed window event. If the window is 
    closed, the window in the software is closed too .Other events may be added here.
*/
void Display::pollEvents()
{
    sf::Event event;

	while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        	_window.close();
    }
}

//! Checks SFML window events.
/*! The only event included here is the closed window event. If the window is 
    closed, the window in the software is closed too .Other events may be added here.
*/
void Display::drawBackground()
{
    _window.draw(_map_sprite);
}

//! Draws a game entity.
/*! Sprites are located in the map using the entity_type. Once that entity is found,
    it is drawn accordingly. 
    \param entity :: Tells Display what entity to draw
    \param draw_info :: Gives information about where the sprite should be drawn
*/
void Display::drawEntity(const entity_type& entity, const sprite_draw_info& draw_info)
{
    std::map<entity_type,std::shared_ptr<sf::Sprite>>::iterator sprite_map_iterator;

    sprite_map_iterator = _sprites.find(entity);

    // Search for the desired entity
    if (sprite_map_iterator != _sprites.end())
    {
        std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
        sprite_sp->setOrigin(draw_info.origin.x, draw_info.origin.y);
        sprite_sp->setPosition(draw_info.draw_pos.x, draw_info.draw_pos.y);
        sprite_sp->setRotation(draw_info.rotation);
        _window.draw(*sprite_sp);
    }
}

//! Draws all text.
/*! All text is received as a string. 
    \param strings :: Holds the strings of all the game text fields.
*/
void Display::drawText(const draw_strings& strings)
{
    _game_time_text.setString(strings.game_time);
    _p1_score_text.setString(strings.p1_score);
    _p2_score_text.setString(strings.p2_score);
    _window.draw(_game_time_text);
    _window.draw(_p1_score_text);
    _window.draw(_p2_score_text);
}

//! Draws the end game screen.
/*! All other sprites are cleared and a single sprite _end_map_sprite is
    drawn.
*/
void Display::drawEndScreen()
{
    _window.clear();
    _window.draw(_end_map_sprite);
}

//! Displays what has been drawn.
/*! Only after everything has been drawn can it be displayed.
*/
void Display::display()
{
    _window.display();
}

