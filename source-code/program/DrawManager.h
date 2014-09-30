/**
 * \class 	DrawManager
 * \file 	DrawManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that manages all drawable objects
 */

#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

//Forward declarations

//Includes
#include "Manager.h"
#include "Deletable.h"
#include "Structures.h"
#include "SpriteDimensions.h"
#include "Display.h"
#include <vector>
#include <map>

class DrawManager: public Manager
{
public:
    /// Constructor for DrawManager
    DrawManager();

    /// Drawing management cycle. The manager will render all the entites within the game world.
	virtual void manage(game_state_info& game_state, std::shared_ptr<Display> display);

	/// Add Drawable-type shared_ptr's to the DrawManagers internal data members
    void addNewEntity(const std::weak_ptr<Deletable> new_entity);

	/// Destructor for DrawManager
	virtual ~DrawManager();

private:
    // Pointers to all drawable entites within the game world
    std::vector<std::weak_ptr<Deletable>> _drawables;

    SpriteDimensions _sprite_dimensions;

    /// Functions to get drawing info based on the entity
    void getTankDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getMissileDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getMineDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getBarrierDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getTurretDrawInfo(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
    void getDrawPosition(std::shared_ptr<Deletable> draw_entity_sp,  sprite_draw_info& draw_info);
};

#endif // DRAWMANAGER_H_
