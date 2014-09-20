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
    //Iterator at initial position within vector
    auto i = _collidables.begin();

	for (; i != _collidables.end(); ++i)
	{
		std::weak_ptr<Collidable> entity_wp = (*i);
		//Convert weak_ptr to shared_ptr
		std::shared_ptr<Collidable> entity_sp = entity_wp.lock();

		const rect_corners& entity_box = (entity_sp)->getBoundingBox(); //Must fix this!!

        //Always one position ahead of iterator i
        auto j =  i+1;

		for (; j != _collidables.end(); ++j)
		{
			std::weak_ptr<Collidable> obstacle_wp = (*j);
			//Convert weak_ptr to shared_ptr
            std::shared_ptr<Collidable> obstacle_sp = obstacle_wp.lock();

			const rect_corners& obstacle_box = (obstacle_sp)->getBoundingBox();

            CollisionHelper collision_helper;// create object of helper class

			if (collision_helper.isCollision(entity_box, obstacle_box))
				setCollisionStates(entity_sp, obstacle_sp);
		}
	}
}

void CollisionManager::setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2)
{
	if ((entity_1->getType() == p1_tank) || (entity_1->getType() == p2_tank))
	{
		switch(entity_2->getType())
		{
			case p1_tank:
				entity_1->setBlocked(); // tank
				entity_2->setBlocked(); // tank
				break;

            case p2_tank:
				entity_1->setBlocked(); // tank
				entity_2->setBlocked(); // tank
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

			default:
				break;
		}
	}
}

void CollisionManager::addNewEntity(std::weak_ptr<Collidable> new_entity)
{
	_collidables.push_back(new_entity);
}

CollisionManager::~CollisionManager()
{

}
