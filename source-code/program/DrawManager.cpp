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
void DrawManager::manage(std::map<entity_type,std::shared_ptr<sf::Sprite>>& game_sprites, sf::RenderWindow& window)
{
    //Clear the screen
    window.clear();

    //Used to traverse the vector of drawables held by DrawManager
    auto draw_itterator = _drawables.begin();

    //Loop through Array of Drawables and draw the corresponding sprite
    for(; draw_itterator != _drawables.end(); draw_itterator++)
    {
        //Deref itterator to weak pointer
        std::weak_ptr<Deletable> draw_entity_wp = (*draw_itterator);
        //Convert to shared pointer
        std::shared_ptr<Deletable> draw_entity_sp = draw_entity_wp.lock();

        switch (draw_entity_sp->getType())
        {
            case p1_tank:
                game_sprites[p1_tank].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p1_tank].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p1_tank]);
                break;

            case p2_tank:
                game_sprites[p2_tank].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p2_tank].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p2_tank]);
                break;

            case barrier:
                game_sprites[barrier].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[barrier].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[barrier]);
                break;

            case p1_missile:
                game_sprites[p1_missile].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p1_missile].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p1_missile]);
                break;

            case p2_missile:
                game_sprites[p2_missile].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p2_missile].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p2_missile]);
                break;

            case p1_mine:
                game_sprites[p1_mine].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p1_mine].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p1_mine]);
                break;

            case p2_mine:
                game_sprites[p2_mine].setPosition(draw_entity_sp->getDrawPositionX(), draw_entity_sp->getDrawPositionY());
                game_sprites[p2_mine].setRotation(draw_entity_sp->getDrawRotation());
                window.draw(game_sprites[p2_mine]);
                break;

            default:
                break;

            //Draw all the sprites
            window.display();
        }
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
