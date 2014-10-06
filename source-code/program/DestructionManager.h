//! Manager class responsible for deletions of destroyed game entities.
/*! The manager is responsible for removing game entities from the game that have been
    destroyed. All game entities are potentially deletable and pointers to these exist within 
    this class.
    \file       DestructionManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#ifndef DESTRUCTIONMANAGER_H_
#define DESTRUCTIONMANAGER_H_

//Includes
#include "Manager.h"
#include "Deletable.h"
#include "GameStateData.h"
#include <vector>

/// Manager class responsible for deletions of destroyed game entities.
class DestructionManager: public Manager
{
public:
    DestructionManager();
    void manage(GameStateData& game_state_container);
    void addNewEntity(std::shared_ptr<Deletable> new_entity);
	virtual ~DestructionManager();

private:
    // Pointers to all destructable entities within the game world
    std::vector<std::shared_ptr<Deletable>> _destructables;
};

#endif // DESTRUCTIONMANAGER_H_
