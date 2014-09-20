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
#include <vector>
#include <map>

class DrawManager: public Manager
{
public:
    /// Constructor for DrawManager
    DrawManager();

    /// Drawing management cycle. The manager will render all the entites within the game world.
	virtual void manage(std::map<entity_type,std::shared_ptr<sf::Sprite>>& game_sprites, sf::RenderWindow& window);

	/// Add Drawable-type shared_ptr's to the DrawManagers internal data members
    void addNewEntity(const std::weak_ptr<Deletable> new_entity);

	/// Destructor for DrawManager
	virtual ~DrawManager();

private:
    // Pointers to all drawable entites within the game world
    std::vector<std::weak_ptr<Deletable>> _drawables;

    sf::Sprite _map;
    sf::Texture _mapText;
    SpriteDimensions _sprite_dimensions;
};

#endif // DRAWMANAGER_H_
