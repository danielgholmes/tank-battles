//! Implementation for CollisionManager class
/*! This manager is responsible for checking and setting the collision and blocked
    states of game entities. It relies upon the GeometryEngine Class for all
    of the geometry related logic conditions.
    \file       CollisionManager.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       2 September 2014
*/

#include "CollisionManager.h"
#include "GeometryEngine.h"
#include <cmath>

CollisionManager::CollisionManager()
{

}

//! Checks and sets the collision status of all game entities
/*! This is the main function of the CollisionManager. The manager iterates through all
    of the collidables and checks it against every other collidable to see if a collision
    has taken place. If an entity that needs to be compared to another entity is blocked,
    it's status is temporarily set as false so that a proper comparison can be made. This
    entity is the entity of the outer for loop.
*/
void CollisionManager::manage()
{

    //Clear all deleted entities from the _collidables vector
    removeGarbage();

    //Iterator at initial position within vector
    auto i = _collidables.begin();
	for (; i != _collidables.end(); ++i)
	{
        bool entity_blocked = false;
        std::weak_ptr<Collidable> entity_wp = (*i);
        //Convert weak_ptr to shared_ptr
        std::shared_ptr<Collidable> entity_sp = entity_wp.lock();

        //Loop through vector of itterators again
        auto j = _collidables.begin();
        for (; j != _collidables.end(); ++j)
        {
            if (i != j)
            {
                std::weak_ptr<Collidable> obstacle_wp = (*j);
                //Convert weak_ptr to shared_ptr
                std::shared_ptr<Collidable> obstacle_sp = obstacle_wp.lock();

                reviewCollisionStates(entity_sp, obstacle_sp, entity_blocked);
            }// if
        }//inner-for
    }//outer-for
}//Manage function

//! Set collision state based on the types of entities that have collided
/*! Different rules for collision apply to different game entities. Different collision functions
    are run based on what entities have collided. Rules for collision can be changed or added here.
    \param entity_1 :: First entity whose collision state will be set 
    \param entity_2 :: Second entity whose collision state will be set 
*/
void CollisionManager::setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
	if ((entity_1->getType() == p1_tank) || (entity_1->getType() == p2_tank))
	{
        tankCollisionReaction(entity_1,entity_2);
	}
	else if ((entity_1->getType() == p1_missile) ||(entity_1->getType() == p2_missile))
	{
        missileCollisionReaction(entity_1,entity_2);
	}

	else if ((entity_1->getType() == p1_mine) || (entity_1->getType() == p2_mine))
	{
        mineCollisionReaction(entity_1,entity_2);
	}

	else if (entity_1->getType() == barrier)
	{
        barrierCollisionReaction(entity_1,entity_2);
	}//Else

	else if (entity_1->getType() == turret)
    {
        turretCollisionReaction(entity_1,entity_2);
    }//Else

    	else if (entity_1->getType() == turret_missile)
    {
        turretMissileCollisionReaction(entity_1,entity_2);
    }//Else
}//Function

//! Resets the blocked states of blocks that were previously blocked, but are not colliding with anything
/*! \param entity :: entity whose blocked state will be changed
*/
void CollisionManager::resetBlockedState(std::shared_ptr<Collidable>& entity)
{
    entity->setUnblocked();
}

//! Add new entity to collidables.
/*! A new entity is added to the private collidables vector, which is used in the main
    manage function.
    \param new_entity :: Entity to be added to collidables vector
*/
void CollisionManager::addNewEntity(std::weak_ptr<Collidable> new_entity)
{
	_collidables.push_back(new_entity);
}

//! Checks to see if two objects have collided base upon their bounding box locations and type
/*! This function excludes barriers. All other entities will have their collision states reviewed.
    The points of the four corners of each entity are used to test if there is a collision.
    \param entity_sp :: Shared pointer to one entity
    \param obstacle_sp :: Shared pointer to the other entity
    \param entity_blocked_status :: blocked status of entity that is being compared to every other entity
*/
void CollisionManager::reviewCollisionStates(std::shared_ptr<Collidable> entity_sp, std::shared_ptr<Collidable> obstacle_sp,
                                             bool& entity_blocked_status)

{
    //This excludes comparing barrier collisions
    if ((obstacle_sp->getType() != barrier) || (entity_sp->getType() != barrier))
    {
        const rect_corners& entity_box = (entity_sp)->getBoundingBox();
        const rect_corners& obstacle_box = (obstacle_sp)->getBoundingBox();

        GeometryEngine geometry_engine;// utilise the geometry engine

        if (geometry_engine.isCollision(entity_box, obstacle_box))
        {
            entity_blocked_status = true;
            setCollisionStates(entity_sp, obstacle_sp);
        }
        if (!entity_blocked_status)
        {
            resetBlockedState(entity_sp);
        }
    }//Barrier comparison if
}

//! Implement logic when a barrier has been collided with a game entity.
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::barrierCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_2->setBlocked(blocked); // tank does not move
        break;

    case p2_tank:
        entity_2->setBlocked(blocked); // tank does not move
        break;

    case p1_missile:
        {
            entity_2->setBlocked(getResultingBlockedStatus(entity_2, entity_1)); // missile rebounds
        }
        break;

    case p2_missile:
        {
            entity_2->setBlocked(getResultingBlockedStatus(entity_2, entity_1)); // missile rebounds
        }
        break;

    case p1_mine:
        entity_2->setCollided();
        break;

    case p2_mine:
        entity_2->setCollided();
        break;

    default:
        break;
    }//Switch

}

//! Implement logic when a mine has collided with a game entity
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::mineCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_1->setCollided(); // mine
        entity_2->setCollided(); // tank
        break;

    case p2_tank:
        entity_1->setCollided(); // mine
        entity_2->setCollided(); // tank
        break;

    case barrier:
        entity_1->setCollided(); //mine
        break;

    case turret:
        entity_1->setCollided();
        break;

    case p1_mine:
        entity_1->setCollided();

    case p2_mine:
        entity_1->setCollided();

    default:
        break;
    }
}

//! Implement logic when a missile has collided with a game entity
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::missileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_1->setCollided(); // missile
        entity_2->setCollided(); // tank
        break;

    case p2_tank:
        entity_1->setCollided(); // missile
        entity_2->setCollided(); // tank
        break;

    case turret:
        entity_1->setCollided(); // turret
        entity_2->setCollided(); // missile

    case p1_missile:
        entity_1->setCollided(); // missile
        entity_2->setCollided(); // missile
        break;

    case p2_missile:
        entity_1->setCollided(); // missile
        entity_2->setCollided(); // missile
        break;

    case barrier:
        if (entity_1->setBlocked(getResultingBlockedStatus(entity_1, entity_2)) <= 0) // missile
            entity_1->setCollided();
        break;

    default:
        break;
    }
}

//! Implement logic when a tank has collided with a game entity.
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::tankCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_1->setBlocked(blocked); // tank
        break;

    case p2_tank:
        entity_1->setBlocked(blocked); // tank
        break;

    case turret:
        entity_1->setBlocked(blocked);
        break;

    case p1_missile:
        entity_1->setCollided(); // tank
        entity_2->setCollided(); // missile
        break;

    case p2_missile:
        entity_1->setCollided(); // tank
        entity_2->setCollided(); // missile
        break;

    case p1_mine:
        entity_1->setCollided(); // tank
        entity_2->setCollided(); // mine
        break;

    case p2_mine:
        entity_1->setCollided(); // tank
        entity_2->setCollided(); // mine
        break;

    case barrier:
        entity_1->setBlocked(blocked); // tank
        break;
    default:
        break;
    }

}

//! Implement logic when a turret has collided with a game entity
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::turretCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_2->setBlocked(blocked); // tank does not move
        break;

    case p2_tank:
        entity_2->setBlocked(blocked); // tank does not move
        break;

    case p1_missile:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    case p2_missile:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    default:
        break;
    }//Switch

}

//! Set the collision or blocked states for a barrier collision.
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
    \return blocked_status
*/
const blocked_status CollisionManager::getResultingBlockedStatus(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    auto entity_collision_box = entity_1->getAlignedBoundingBox();
    auto object_collision_box = entity_2->getAlignedBoundingBox();
    GeometryEngine geometry_engine;
    return (geometry_engine.getRelativePosition(entity_collision_box,object_collision_box));
}

//! Implement logic when a turret missile has collided with a game entity.
/*! \param entity_1 :: First entity that will have its status changed
    \param entity_2 :: Second entity that will have its status changed
*/
void CollisionManager::turretMissileCollisionReaction(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    switch(entity_2->getType())
    {
    case p1_tank:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    case p2_tank:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    case p1_missile:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    case p2_missile:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    case barrier:
        entity_1->setCollided();
        break;

    case p1_mine:
        break; //Do nothing

    case p2_mine:
        break; //Do nothing

    case turret_missile:
        entity_1->setCollided();
        entity_2->setCollided();
        break;

    default:
        break;
    }//Switch
}

//! Helper function to remove 'Dead' entities from collision manager.
/*! 
*/
void CollisionManager::removeGarbage()
{
    auto removal = _collidables.begin();
    for (; removal != _collidables.end();)
    {
        std::weak_ptr<Collidable> removal_wp = (*removal);
		//Convert weak_ptr to shared_ptr
		std::shared_ptr<Collidable> removal_sp = removal_wp.lock();
		//Test if pointer still valid
		if(removal_sp)
        {
            removal++;
        }
        else
        {
            _collidables.erase(removal);
        }
    }
}

CollisionManager::~CollisionManager()
{

}
