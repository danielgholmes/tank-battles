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
#include <vector>

class DrawManager: public Manager
{
public:
    /// Constructor for DrawManager
    DrawManager();

    /// Drawing management cycle. The manager will render all the entites within the game world.
	virtual void manage(std::vector<sf::Sprite>& game_sprites, const textures& game_textures);

	/// Add Drawable-type shared_ptr's to the DrawManagers internal data members
    void addNewEntity(const std::weak_ptr<Deletable> new_entity);

	/// Destructor for DrawManager
	virtual ~DrawManager();

private:
    // Pointers to all drawable entites within the game world
    std::vector<std::weak_ptr<Deletable>> _drawables;
};

#endif // DRAWMANAGER_H_
