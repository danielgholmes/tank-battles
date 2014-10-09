//! Manager class responsible for managing collisions.
/*! This manager is responsible for checking and setting the collision
    states of game entities. It relies upon the GeometryEngine Class for all
    of the geometry related logic conditions.
    \file       CollisionManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

//includes
#include "Manager.h"
#include "Collidable.h"
#include "Structures.h"

/// Manager class responsible for managing collisions.
class CollisionManager: public Manager
{
public:
    CollisionManager();
    void manage();
    void addNewEntity(std::weak_ptr<Collidable>  new_entity);
	virtual ~CollisionManager();

private:
    ///Pointers to all collidable entities within the game world
    std::vector<std::weak_ptr<Collidable>> _collidables;

	const blocked_status getResultingBlockedStatus(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void reviewCollisionStates(std::shared_ptr<Collidable> entity_sp, std::shared_ptr<Collidable> obstacle_sp, bool& entity_blocked_status);
	void setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void tankCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void missileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void mineCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void barrierCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void turretCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
    void turretMissileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);
	void resetBlockedState(std::shared_ptr<Collidable>& entity);
	void removeGarbage();
};

#endif // COLLISIONMANAGER_H_
