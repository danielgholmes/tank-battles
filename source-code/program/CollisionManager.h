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
	virtual ~CollisionManager();

private:
    ///Pointers to all collidable entities within the game world
    std::vector<std::weak_ptr<Collidable>> _collidables;
    ///Checks to see if two objects have collided base upon their bounding box locations and type
    void reviewCollisionStates(std::shared_ptr<Collidable> entity_sp, std::shared_ptr<Collidable> obstacle_sp, bool& entity_blocked_status);
	///Set collision state based on the types of entities that have collided
	void setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a tank has collided with a game entity
    void tankCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a missile has collided with a game entity
    void missileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a mine has collided with a game entity
    void mineCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a barrier has been collided with a game entity
    void barrierCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a turret has collided with a game entity
    void turretCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    ///Implement logic when a turret missile has collided with a game entity
    void turretMissileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
	///Resets the blocked states of blocks that were previously blocked, by are not colliding with anything
	void resetBlockedState(std::shared_ptr<Collidable>& entity);
	///Helper function to remove 'Dead' entities from collision manager
	void removeGarbage();

};

#endif // COLLISIONMANAGER_H_
