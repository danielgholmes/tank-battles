/**
 * \class 	DestructionManager
 * \file 	DestructionManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that manages all destructable objects
 */

#ifndef DESTRUCTIONMANAGER_H_
#define DESTRUCTIONMANAGER_H_

//Forward declarations
//class weak_ptr;

//Includes
#include "Manager.h"
#include "Deletable.h"
#include <vector>

class DestructionManager: public Manager
{
public:
    /// Constructor for the Destruction manager
    DestructionManager();

    /// Destruction management process for the Destruction Manager
    void manage(bool& game_state);

	/// Add Deletable-type shared_ptr's to the DestructionManagers internal data members
    void addNewEntity(std::shared_ptr<Deletable> new_entity);

    /// Destructor for the destruction manager
	virtual ~DestructionManager();

private:
    // Pointers to all destructable entities within the game world
    std::vector<std::shared_ptr<Deletable>> _destructables;
};

#endif // DESTRUCTIONMANAGER_H_
