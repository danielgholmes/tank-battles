/**
 * /file 	DrawManager.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for DrawManager class
 */

#include "DrawManager.h"

///Constructor for DrawManager
DrawManager::DrawManager()
{

}

///Drawing management cycle. The manager will render all the entites within the game world.
void DrawManager::manage(std::vector<sf::Sprite>& game_sprites, const textures& game_textures)
{
    //Clear current sprite entities for drawing
    game_sprites.empty();
    //Used to traverse the vector of drawables held by DrawManager
    auto draw_itterator = _drawables.begin();
    //Will hold the position value of each drawable entity within the game
    sf::Vector2f temp_position;
    //Will hold the rotation value of each drawable entity within the game
    float temp_rotation = 0.0;

    for(; draw_itterator != _drawables.end(); draw_itterator++)
    {
        //Dereference itterator to weak pointer
        std::weak_ptr<Deletable> entity_wp = (*draw_itterator);
        //Create a shared pointer to act on the object
        std::shared_ptr<Deletable> entity_sp = entity_wp.lock();

        temp_position = entity_sp->getDrawPosition();
        temp_rotation = entity_sp->getDrawRotation();

        //Creation of the temp sprite and assigning its states
        sf::Sprite temp_sprite;
        temp_sprite.setPosition(temp_position);
        temp_sprite.setRotation(temp_rotation);

        //Correctly assigning textures to each image
        if(entity_sp->getType() == p1_tank)
        {
            temp_sprite.setTexture(game_textures.tank_1);
        }
        if(entity_sp->getType() == p2_tank)
        {
            temp_sprite.setTexture(game_textures.tank_2);
        }
        if((entity_sp->getType() == p1_missile) || (entity_sp->getType() == p2_missile))
        {
             temp_sprite.setTexture(game_textures.missile);
        }
        if((entity_sp->getType() == p1_mine) || (entity_sp->getType() == p2_mine))
        {
            temp_sprite.setTexture(game_textures.mine);
        }
        if(entity_sp->getType() == barrier)
        {
            temp_sprite.setTexture(game_textures.barrier);
        }

        //add the new sprite to the world
        game_sprites.push_back(temp_sprite);
    }
}
///Destructor for DrawManager
DrawManager::~DrawManager()
{

}

void DrawManager::addNewEntity(const std::weak_ptr<Deletable> new_entity)
{
	_drawables.push_back(new_entity);
}
