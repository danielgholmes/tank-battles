//! Manager class responsible for preparing draw data.
/*! This manager is part of the view module. It collects all relevant data for the
    Display class for drawing. This manager does not changed any data.
    \file       DrawManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

//Includes
#include "Manager.h"
#include "Deletable.h"
#include "Structures.h"
#include "SpriteDimensions.h"
#include "GameStateData.h"
#include "Display.h"
#include <vector>
#include <map>

/// Manager class responsible for preparing draw data.
class DrawManager: public Manager
{
public:
    DrawManager();
	virtual void manage(GameStateData& game_state_container, std::shared_ptr<Display> display);
    void addNewEntity(const std::weak_ptr<Deletable> new_entity);
	virtual ~DrawManager();

private:
    /// Pointers to all drawable entites within the game world
    std::vector<std::weak_ptr<Deletable>> _drawables;
    /// Private data object that holds sprite dimension info
    SpriteDimensions _sprite_dimensions;

    // Functions to get drawing info based on the entity
    void getTankDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getMissileDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getMineDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getBarrierDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getTurretDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getDrawPosition(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
};

#endif // DRAWMANAGER_H_
