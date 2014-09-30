/**
 * /file 	DrawManager.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for DrawManager class
 */

#include "DrawManager.h"
#include <iostream>
#include <sstream>
#include <string>

///Constructor for DrawManager
DrawManager::DrawManager():
    _sprite_dimensions()
{

}

///Drawing management cycle. The manager will render all the entites within the game world.
void DrawManager::manage(GameStateData& game_state_container, std::shared_ptr<Display> display)
{
    sprite_draw_info draw_info;
    //Used to traverse the vector of drawables held by DrawManager
    auto draw_itterator = _drawables.begin();

    //Loop through Array of Drawables and draw the corresponding sprite
    for(;draw_itterator != _drawables.end();)
    {
        //Deref itterator to weak pointer
        std::weak_ptr<Deletable> draw_entity_wp = (*draw_itterator);
        //Convert to shared pointer
        std::shared_ptr<Deletable> draw_entity_sp = draw_entity_wp.lock();
        //Check to see if the entity still exists
        if(draw_entity_sp)
        {
            switch (draw_entity_sp->getType())
            {
                case p1_tank:
                    getTankDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p1_tank, draw_info);
                    break;

                case p2_tank:
                    getTankDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p2_tank, draw_info);
                    break;

                case barrier:
                    getBarrierDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(barrier, draw_info);
                    break;

                case p1_missile:
                    getMissileDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p1_missile, draw_info);
                    break;

                case p2_missile:
                    getMissileDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p2_missile, draw_info);
                    break;

                case p1_mine:
                    getMineDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p1_mine, draw_info);
                    break;

                case p2_mine:
                    getMineDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(p2_mine, draw_info);
                    break;

                case turret:
                    getTurretDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(turret, draw_info);
                    break;

                case turret_missile:
                    getMineDrawInfo(draw_entity_sp, draw_info);
                    display->addSpriteToDraw(turret, draw_info);
                    break;

                default:
                break;

            } //Switch
            draw_itterator++;
        } //if (pointer still valid)
        else
            _drawables.erase(draw_itterator);

    } //for

    draw_strings strings;

    std::ostringstream strs1;
    strs1 << game_state.runtime;
    strings.game_time = strs1.str();

    std::ostringstream strs2;
    strs2 << game_state_container.getP1Score();
    strings.p1_score = strs2.str();

    std::ostringstream strs3;
    strs3 << game_state_container.getP2Score();
    strings.p2_score = strs3.str();

    display->addTextToDraw(strings);
}

void DrawManager::getTankDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.tank_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.tank_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

void DrawManager::getMissileDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.missile_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.missile_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

void DrawManager::getMineDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.mine_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.mine_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

void DrawManager::getTurretDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.turret_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.turret_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

void DrawManager::getDrawPosition(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.draw_pos.x = draw_entity_sp->getDrawPositionX();
    draw_info.draw_pos.y = draw_entity_sp->getDrawPositionY();
}

void DrawManager::addNewEntity(const std::weak_ptr<Deletable> new_entity)
{
	_drawables.push_back(new_entity);
}

///Destructor for DrawManager
DrawManager::~DrawManager()
{

}
