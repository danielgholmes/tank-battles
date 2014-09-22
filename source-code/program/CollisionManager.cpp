/**
 * \file 	CollisionManager.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for CollisionManager class
 */

#include "CollisionManager.h"
#include "CollisionHelper.h""
#include <cmath>

CollisionManager::CollisionManager()
{

}

void CollisionManager::manage()
{

	 //Clear all deleted entities from the _collidables vector
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

    //Iterator at initial position within vector
    auto i = _collidables.begin();
	for (; i != _collidables.end(); ++i)
	{
        bool entity_blocked = false;
        std::weak_ptr<Collidable> entity_wp = (*i);
        //Convert weak_ptr to shared_ptr
        std::shared_ptr<Collidable> entity_sp = entity_wp.lock();

        const rect_corners& entity_box = (entity_sp)->getBoundingBox();

        //Always one position ahead of iterator i
        auto j = _collidables.begin();
        for (; j != _collidables.end(); ++j)
        {
            if (i != j)
            {
                std::weak_ptr<Collidable> obstacle_wp = (*j);
                //Convert weak_ptr to shared_ptr
                std::shared_ptr<Collidable> obstacle_sp = obstacle_wp.lock();

                //This excludes comparing barrier collisions
                if ((obstacle_sp->getType() != barrier) || (entity_sp->getType() != barrier))
                {
                    const rect_corners& obstacle_box = (obstacle_sp)->getBoundingBox();

                    CollisionHelper collision_helper;// create object of helper class

                    if (collision_helper.isCollision(entity_box, obstacle_box))
                    {
                        entity_blocked = true;
                        setCollisionStates(entity_sp, obstacle_sp);
                    }
                    if (!entity_blocked)
                    {
                        resetBlockedState(entity_sp);
                    }
                }//Barrier comparison if
            }//itterator if
        }//inner-for
    }//outer-for
}//Manage function


void CollisionManager::setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
	if ((entity_1->getType() == p1_tank) || (entity_1->getType() == p2_tank))
	{
		switch(entity_2->getType())
		{
			case p1_tank:
				entity_1->setBlocked(); // tank
//				entity_2->setBlocked(); // tank
				break;

            case p2_tank:
				entity_1->setBlocked(); // tank
//				entity_2->setBlocked(); // tank
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
				entity_1->setBlocked(); // tank
				break;
			default:
				break;
		}
	}
	else if ((entity_1->getType() == p1_missile) ||(entity_1->getType() == p2_missile) )
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

			case p1_missile:
				entity_1->setCollided(); // missile
				entity_2->setCollided(); // missile
				break;

            case p2_missile:
				entity_1->setCollided(); // missile
				entity_2->setCollided(); // missile
				break;

			case barrier:
				entity_1->setBlocked(); // missile
				break;

			default:
				break;
		}
	}

	else if ((entity_1->getType() == p1_mine) || (entity_1->getType() == p2_mine))
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

			default:
				break;
		}
	}

	else if (entity_1->getType() == barrier)
	{
		switch(entity_2->getType())
		{
			case p1_tank:
				entity_2->setBlocked(); // tank does not move
				break;

            case p2_tank:
				entity_2->setBlocked(); // tank does not move
				break;

			case p1_missile:
				entity_2->setBlocked(); // missile rebounds
				break;

            case p2_missile:
				entity_2->setBlocked(); // missile rebounds
				break;

            case p1_mine:
                entity_2->setCollided();
                break;

            case p2_mine:
                entity_2->setCollided();
                break;

			default:
				break;
		}
	}
}

void CollisionManager::resetBlockedState(std::shared_ptr<Collidable>& entity)
{
  entity->setUnblocked();
}

void CollisionManager::addNewEntity(std::weak_ptr<Collidable> new_entity)
{
	_collidables.push_back(new_entity);
}

CollisionManager::~CollisionManager()
{

}
