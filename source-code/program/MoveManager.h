//! Manager responsible for moving all movable objects.
/*! This class is responsible for performing all movement associated logic
    within the game world. It acts upon all movables and has access to
    their member functions.
    \file 	    MoveManager.h
    \author 	Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date 	    2 September 2014
 */

#ifndef MOVEMANAGER_H_
#define MOVEMANAGER_H_

//Includes
#include "Manager.h"
#include "Structures.h"
#include "Movable.h"
#include "ActionData.h"
#include <vector>

class MoveManager: public Manager
{
public:
    /// Constructor
    MoveManager();

    /// Move all movable entities within the world
    void manage(const ActionData& action_data_container);

	/// Add Movable-type shared_ptr's to the MoveManagers internal data members
    void addNewEntity(std::weak_ptr<Movable> new_entity);

	/// Destructor for MoveManager
	virtual ~MoveManager();

private:
    // Pointers to all moveable entities within the game world
    std::vector<std::weak_ptr<Movable>> _movables;

    //Helper function
    void removeGarbage();
};

#endif // MOVEMANAGER_H_
