/**
 * /file 	DrawManager.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for DrawManager class
 */

#include "DrawManager.h"
#include <iostream>
#include <sstream>

///Constructor for DrawManager
DrawManager::DrawManager():
    _sprite_dimensions()
{
   if (!_mapText.loadFromFile("map.png"))
   {
        std::cout << "Unable to load Map file!" << std::endl;
   }
   _map.setTexture(_mapText);

   if (!_font.loadFromFile("futura_light.ttf"))
   {
       std::cout << "Unable to load font file!" << std::endl;
   }
    // select the font
    _game_time_text.setFont(_font);
    _game_time_text.setCharacterSize(20);
    _game_time_text.setColor(sf::Color::White);
    _game_time_text.setStyle(sf::Text::Bold);
    _game_time_text.setPosition(550,0);
}

///Drawing management cycle. The manager will render all the entites within the game world.
void DrawManager::manage(std::map<entity_type,std::shared_ptr<sf::Sprite>>& game_sprites, sf::RenderWindow& window, game_state_info& game_state)
{
    //Clear the screen
    window.clear();

    //Draw the Map
    window.draw(_map);

    //Used to traverse the vector of drawables held by DrawManager
    auto draw_itterator = _drawables.begin();

    //Loop through Array of Drawables and draw the corresponding sprite
    for(;draw_itterator != _drawables.end();)
    {
        //Deref itterator to weak pointer
        std::weak_ptr<Deletable> draw_entity_wp = (*draw_itterator);
        //Convert to shared pointer
        std::shared_ptr<Deletable> draw_entity_sp = draw_entity_wp.lock();
        //Map itterator to traverse container
        std::map<entity_type,std::shared_ptr<sf::Sprite>>::iterator sprite_map_iterator;
        //Check to see if the entity still exists
        if(draw_entity_sp)
        {
            switch (draw_entity_sp->getType())
            {
                case p1_tank:
                //Search the map for p1_tank sprite
                sprite_map_iterator = game_sprites.find(p1_tank);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.tank_sprite_x/2, _sprite_dimensions.tank_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case p2_tank:
                 //Search the map for p2_tank sprite
                sprite_map_iterator = game_sprites.find(p2_tank);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.tank_sprite_x/2, _sprite_dimensions.tank_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case barrier:
                //Search the map for barrier sprite
                sprite_map_iterator = game_sprites.find(barrier);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.barrier_sprite_x/2, _sprite_dimensions.barrier_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case p1_missile:
                 //Search the map for p1_missile sprite
                sprite_map_iterator = game_sprites.find(p1_missile);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.missile_sprite_x/2, _sprite_dimensions.missile_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case p2_missile:
                //Search the map for p2_missile sprite
                sprite_map_iterator = game_sprites.find(p2_missile);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.missile_sprite_x/2, _sprite_dimensions.missile_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case p1_mine:
                 //Search the map for p1_mine sprite
                sprite_map_iterator = game_sprites.find(p1_mine);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.mine_sprite_x/2, _sprite_dimensions.mine_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                case p2_mine:
                //Search the map for p2_mine sprite
                sprite_map_iterator = game_sprites.find(p2_mine);
                if (sprite_map_iterator != game_sprites.end())
                {
                    std::shared_ptr<sf::Sprite> sprite_sp = sprite_map_iterator->second;
                    sprite_sp->setOrigin(_sprite_dimensions.mine_sprite_x/2, _sprite_dimensions.mine_sprite_y/2);
                    sprite_sp->setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                    sprite_sp->setRotation(draw_entity_sp->getDrawRotation());
                    window.draw(*sprite_sp);
                }
                break;

                default:
                break;

            } //Switch
            draw_itterator++;
        } //if (pointer still valid)
        else
            {
                _drawables.erase(draw_itterator);
            }
    } //for

    std::ostringstream strs; // convert time double to string
    strs << game_state.runtime;
    std::string str = strs.str();

    _game_time_text.setString(str);
    window.draw(_game_time_text);

    window.display();
}
///Destructor for DrawManager
DrawManager::~DrawManager()
{

}

void DrawManager::addNewEntity(const std::weak_ptr<Deletable> new_entity)
{
	_drawables.push_back(new_entity);
}
