//! Implementation for the DrawManager class.
/*! This manager is part of the view module. It collects all relevant data for the
    Display class for drawing. This manager does not changed any data.
    \file       DrawManager.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#include "DrawManager.h"
#include <iostream>
#include <sstream>
#include <string>

//! Draw manager object constructor.
/*! Create the sprite dimensions object
*/
DrawManager::DrawManager():
    _sprite_dimensions()
{

}

//! Drawing management cycle. 
/*! Main function of the DrawManager. The display object is accessable within here. The DrawManager
    first gets the display to clear the window and display the background. Then all drawables are
    iterated through and drawn. Info is collected based on the entity that will be drawn. This 
    information is passed to the display object which actually performs the drawing.
    \param game_state_container :: Game data that hold the time and player scores to be drawn
    \param display :: The display to which display information is passed.
*/
void DrawManager::manage(GameStateData& game_state_container, std::shared_ptr<Display> display)
{
    display->clear();
    display->drawBackground();

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
                    display->drawEntity(p1_tank, draw_info);
                    break;

                case p2_tank:
                    getTankDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(p2_tank, draw_info);
                    break;

                case barrier:
                    getBarrierDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(barrier, draw_info);
                    break;

                case p1_missile:
                    getMissileDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(p1_missile, draw_info);
                    break;

                case p2_missile:
                    getMissileDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(p2_missile, draw_info);
                    break;

                case p1_mine:
                    getMineDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(p1_mine, draw_info);
                    break;

                case p2_mine:
                    getMineDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(p2_mine, draw_info);
                    break;

                case turret:
                    getTurretDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(turret, draw_info);
                    break;

                case turret_missile:
                    getMissileDrawInfo(draw_entity_sp, draw_info);
                    display->drawEntity(turret_missile, draw_info);
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

    std::ostringstream strs1; // convert to strings
    strs1 << game_state_container.getGameTime();
    strings.game_time = strs1.str();

    std::ostringstream strs2;
    strs2 << game_state_container.getP1Score();
    strings.p1_score = strs2.str();

    std::ostringstream strs3;
    strs3 << game_state_container.getP2Score();
    strings.p2_score = strs3.str();

    display->drawText(strings);
    display->display();
}

//! Gets info for tank to be drawn.
/*! This info includs the origin and position of the tank.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getTankDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.tank_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.tank_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

//! Gets info for barrier to be drawn.
/*! This info includs the origin and position of the barrier.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getBarrierDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.barrier_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.barrier_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

//! Gets info for missile to be drawn.
/*! This info includs the origin and position of the missile.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getMissileDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.missile_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.missile_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

//! Gets info for mine to be drawn.
/*! This info includs the origin and position of the mine.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getMineDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.mine_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.mine_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

//! Gets info for turret to be drawn.
/*! This info includs the origin and position of the turret.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getTurretDrawInfo(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.origin.x = _sprite_dimensions.turret_sprite_x/2;
    draw_info.origin.y = _sprite_dimensions.turret_sprite_y/2;
    getDrawPosition(draw_entity_sp, draw_info);
}

//! Gets info for an entity to be drawn.
/*! This info includs the origin and position of the entity.
    \param draw_entity_sp :: shared pointer to the object from which info will be extracted
    \param draw_info :: Info that will be updated with the entity draw position info.
*/
void DrawManager::getDrawPosition(std::shared_ptr<Deletable> draw_entity_sp, sprite_draw_info& draw_info)
{
    draw_info.draw_pos.x = draw_entity_sp->getDrawPositionX();
    draw_info.draw_pos.y = draw_entity_sp->getDrawPositionY();
    draw_info.rotation = draw_entity_sp->getDrawRotation();
}

//! Adds a pointer to a drawable object.
/*! A weak pointer is saved to the private vector of the DrawManager
    \param new_entity :: weak pointer to entity that will be added
*/
void DrawManager::addNewEntity(const std::weak_ptr<Deletable> new_entity)
{
	_drawables.push_back(new_entity);
}

//Destructor for DrawManager
DrawManager::~DrawManager()
{

}
