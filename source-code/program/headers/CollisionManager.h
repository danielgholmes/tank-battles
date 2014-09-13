/**
 * \class 	CollisionManager
 * \file 	CollisionManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that manages all collidable objects
 */


#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

//Forward declarations

//includes
#include "Manager.h"
#include "Collidable.h"


class CollisionManager: public Manager
{
public:
    /// Collision manager constructor
    CollisionManager();

	/// Check and assign collision states of all collidable entities
    void manage();

	/// Add Collidable-type shared_ptr's to the CollisionManagers internal data members
    void addNewEntity(std::weak_ptr<Collidable>  new_entity);

    /// Collision manager destructor
	~CollisionManager();

private:
    // Pointers to all collidable entities within the game world
    std::vector<std::weak_ptr<Collidable>> _collidables;

	/// Set collision state based on the types of entities that have collided
	void setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);

};

#endif // COLLISIONMANAGER_H_
