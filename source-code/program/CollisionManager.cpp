/**
 * \file 	CollisionManager.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for CollisionManager class
 */

#include "CollisionManager.h"
#include "GeometryEngine.h"
#include <cmath>

CollisionManager::CollisionManager()
{

}

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

void CollisionManager::resetBlockedState(std::shared_ptr<Collidable>& entity)
{
  entity->setUnblocked();
}

void CollisionManager::addNewEntity(std::weak_ptr<Collidable> new_entity)
{
	_collidables.push_back(new_entity);
}

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

const blocked_status CollisionManager::getResultingBlockedStatus(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
    auto entity_collision_box = entity_1->getBoundingBox();
    auto object_collision_box = entity_2->getBoundingBox();
    GeometryEngine geometry_engine;
    return (geometry_engine.getRelativePosition(entity_collision_box,object_collision_box));
}

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
