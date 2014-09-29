/**
 * \file 	Display.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	29 September 2014
 * \brief 	Implementation for SFML display class
 */

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Display.h"
#include <iostream>

Display::Display(int window_width, int window_height):
    _window_width(window_width),
    _window_height(window_height)
{
    loadTextures();
    addSprites();

    if (!_map_texture.loadFromFile(_map_texture_file))
        std::cout << "Unable to load Map file!" << std::endl;

    _map_sprite.setTexture(_map_texture);

    if (!_font_style.loadFromFile(_font_file))
       std::cout << "Unable to load font file!" << std::endl;

    setupText(_game_time_text);
    _game_time_text.setPosition(_game_time_pos,_text_y_allignment);

    setupText(_p1_score_text);
    _p1_score_text.setPosition(_p1_score_pos,_text_y_allignment);

    setupText(_p2_score_text);
    _p2_score_text.setPosition(_p2_score_pos,_text_y_allignment);

	sf::RenderWindow _window(sf::VideoMode(_window_width, _window_height), _window_title);
	_window.setFramerateLimit(45);

}

void Display::setupText(sf::Text& text)
{
    text.setFont(_font_style);
    text.setCharacterSize(_font_size);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
}

void Display::loadTextures()
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

void Display::addSprites()
{
//    for (int entity_enum = p1_tank; entity_enum != turret; entity_enum++)
//    {
//        entity_type entity = static_cast<entity_type>(entity_enum);
//        std::shared_ptr<sf::Sprite> entity_sp(new(sf::Sprite));
//        entity_sp->setTexture(_game_textures.tank_1);
//        _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(p1_tank,tank1_sp));
//    }
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

    //Create Turret Sprite
    std::shared_ptr<sf::Sprite> turret_missile_sp(new(sf::Sprite));
    turret_missile_sp->setTexture(_game_textures.missile_turret);
    _sprites.insert(std::pair<entity_type, std::shared_ptr<sf::Sprite>>(turret_missile,turret_missile_sp));
}

void Display::pollEvents()
{
    sf::Event event;

	while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        	_window.close();
    }
}
// Needs to get the dimensions from the draw manager
void Display::addSpritesToDraw(const entity_type& entity, const sprite_draw_info& draw_info)
{
    std::map<entity_type,std::shared_ptr<sf::Sprite>>::iterator sprite_map_iterator;

    sprite_map_iterator = _sprites.find(entity);

    if (sprite_map_iterator != _sprites.end())
    {
        std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
        sprite_sp->setOrigin(draw_info.origin.x/2, draw_info.origin.y/2);
        sprite_sp->setPosition(draw_info.draw_pos.x, draw_info.draw_pos.y);
        sprite_sp->setRotation(draw_info.rotation);
        _drawings.push_back(sprite_sp);
    }
}

void Display::drawAndDisplayEverything()
{
    _window.clear();

    _window.draw(_map_sprite);

    auto sprite = _drawings.begin();
    for (; sprite != _drawings.end(); sprite++)
        _window.draw(*(*sprite));

    _window.draw(_game_time_text);
    _window.draw(_p1_score_text);
    _window.draw(_p2_score_text);

    _window.display();
}

void Display::addTextToDraw(const draw_strings& strings)
{
    _game_time_text.setString(strings.game_time);
    _p1_score_text.setString(strings.p1_score);
    _p2_score_text.setString(strings.p2_score);
}
