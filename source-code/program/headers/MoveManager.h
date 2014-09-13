/**
 * \class 	MoveManager
 * \file 	MoveManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that moves all movable objects
 */

#ifndef MOVEMANAGER_H_
#define MOVEMANAGER_H_

//Forward Declarations
//class weak_ptr;

//Includes
#include "Manager.h"
#include "Game.h"
#include <vector>

class MoveManager: public Manager
{
public:
    /// Constructor
    MoveManager();

    /// Move all movable entities within the world
    void manage(const actions_info& managerInstructions);

	/// Add Movable-type shared_ptr's to the MoveManagers internal data members
    void addNewEntity(std::weak_ptr<Movable> new_entity);

	/// Destructor for MoveManager
	~MoveManager();

private:
    // Pointers to all moveable entities within the game world
    std::vector<std::weak_ptr<Movable>> _movables;
};

#endif // MOVEMANAGER_H_
