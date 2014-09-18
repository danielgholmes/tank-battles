/**
 * \file 	CollisionManager.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for CollisionManager class
 */

#include "CollisionManager.h"
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

			if (isCollision(entity_box, obstacle_box))
				setCollisionStates(entity_sp, obstacle_sp);
		}
	}
}

///Algorithm based on the separating axis theorem
bool CollisionManager::isCollision(const rect_corners& rect_A, const rect_corners& rect_B)
{
	std::vector<coordinate> axes; // container for all axes
    coordinate axis1; // *vector would be a better description than coordinate
    coordinate axis2;
    coordinate axis3;
    coordinate axis4;

    // initialise axis for projecting vertices onto
    axis1.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis1.y = rect_A.upper_right.y - rect_A.upper_left.y;
    axes.push_back(axis1);
    axis2.x = rect_A.upper_right.x - rect_A.lower_right.x;
    axis2.y = rect_A.upper_right.y - rect_A.lower_right.y;
    axes.push_back(axis2);
    axis3.x = rect_B.upper_left.x - rect_B.lower_left.x;
    axis3.y = rect_B.upper_left.y - rect_B.lower_left.y;
    axes.push_back(axis3);
    axis4.x = rect_B.upper_left.x - rect_B.upper_right.x;
    axis4.y = rect_B.upper_left.y - rect_B.upper_right.y;
    axes.push_back(axis4);

    // iterate through all axes
    auto axis = axes.begin();
    for (; axis != axes.end(); ++axis)
    {
    	if (!isOverlap(*axis, rect_A, rect_B));
    		return false; // if there is at least one axis where no overlap has occurred, then there is no collision
    }
    return true; // return true if each axis has an overlap
}

bool CollisionManager::isOverlap(const coordinate& axis, const rect_corners& rect_A, const rect_corners& rect_B)
{
	float max_A, max_B = 0.0; // scalar values of dot products between axis and projection
	float min_A, min_B = 0.0;

    std::vector<coordinate> axis_projections;

    calculateAllProjections(axis_projections, rect_A, axis);
    calculateAllProjections(axis_projections, rect_B, axis);

    calculateMaxAndMinProjections(axis_projections, rect_A, axis, max_A, min_A);
    calculateMaxAndMinProjections(axis_projections, rect_B, axis, max_B, min_B);

    if ((min_B <= max_A) && (max_B >= min_A))
    	return true;
    else
    	return false;
}

void CollisionManager::calculateAllProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis)
{
	coordinate point;

    point.x = ((rect.upper_right.x*axis.x + rect.upper_right.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.x;
    point.y = ((rect.upper_right.x*axis.x + rect.upper_right.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.y;
    axis_projections.push_back(point);

    point.x = ((rect.upper_left.x*axis.x + rect.upper_left.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.x;
    point.y = ((rect.upper_left.x*axis.x + rect.upper_left.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.y;
    axis_projections.push_back(point);

    point.x = ((rect.lower_right.x*axis.x + rect.lower_right.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.x;
    point.y = ((rect.lower_right.x*axis.x + rect.lower_right.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.y;
    axis_projections.push_back(point);

    point.x = ((rect.lower_left.x*axis.x + rect.lower_left.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.x;
    point.y = ((rect.lower_left.x*axis.x + rect.lower_left.y*axis.y)/(powf(axis.x, 2.0) + powf(axis.y, 2.0)))*axis.y;
    axis_projections.push_back(point);
}


void CollisionManager::calculateMaxAndMinProjections(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min)
{
	std::vector<float> projection_pos; // container that will indicate the projection position along axis

	auto projection = axis_projections.begin();
	for (; projection != axis_projections.end(); ++projection)
		projection_pos.push_back(((projection->x)*axis.x) + ((projection->y)*axis.y));

	min = *std::min_element(projection_pos.begin(), projection_pos.end());
	max = *std::max_element(projection_pos.begin(), projection_pos.end());
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
