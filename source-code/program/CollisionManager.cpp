/**
 * \file 	CollisionManager.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Implementation for CollisionManager class
 */

#include "CollisionManager.h"

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

        //Always one position ahead of itterator i
        auto j =  i+1;

		for (; j != _collidables.end(); ++j)
		{
			std::weak_ptr<Collidable> obstacle_wp = (*j);
			//Convert weak_ptr to shared_ptr
            std::shared_ptr<Collidable> obstacle_sp = obstacle_wp.lock();

			const rect_corners& obstacle_box = (obstacle_sp)->getBoundingBox();

//			if (entity_box.intersects(obstacle_box))
//				setCollisionStates(entity_sp, obstacle_sp);
		}
	}
}

///Algorithm based on the separating axis theorem
bool CollisionManager::isCollision(rect_corners rect_A, rect_corners rect_B)
{
    coordinate axis1;
    coordinate axis2;
    coordinate axis3;
    coordinate axis4;

    // Determine axis for projecting vertices onto
    axis1.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis1.y = rect_A.upper_right.y - rect_a.upper_left.y;
    axis2.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis2.y = rect_A.upper_right.y - rect_A.upper_left.y;
    axis3.x = rect_B.upper_right.x - rect_B.upper_left.x;
    axis3.y = rect_B.upper_right.y - rect_B.upper_left.y;
    axis4.x = rect_B.upper_right.x - rect_B.upper_left.x;
    axis4.y = rect_B.upper_right.y - rect_B.upper_left.y;

    //need 8 (x,y) points that will give the position of each of the rectangles points projected onto
    //the axis

    //once we have this, we do the dot product of these points with axis

}

void CollisionManager::projectCornersOntoAxis(coordinate axis, rect_corners rect_A, rect_corners rect_B)
{
    std::vector<coordinate> axis_projections;
    coordinate point;



    //calculateProjection(projected_vectors_A, rect_A, axis);
    //calculateProjection(projected_vectors_B, rect_B, axis);


}

void CollisionManager::calculateProjection(rect_corners& projected_vectors, rect_corners& rect, coordinate axis)
{
    projected_vectors.upper_right.x = ((rect.upper_right.x*axis.x + rect.upper_right.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.x;
    projected_vectors.upper_right.y = ((rect.upper_right.x*axis.x + rect.upper_right.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.y;
    projected_vectors.upper_left.x = ((rect.upper_left.x*axis.x + rect.upper_left.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.x;
    projected_vectors.upper_left.y = ((rect.upper_left.x*axis.x + rect.upper_left.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.y;
    projected_vectors.lower_right.x = ((rect.lower_right.x*axis.x + rect.lower_right.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.x;
    projected_vectors.lower_right.y = ((rect.lower_right.x*axis.x + rect.lower_right.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.y;
    projected_vectors.lower_left.x = ((rect.lower_left.x*axis.x + rect.lower_left.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.x;
    projected_vectors.lower_left.y = ((rect.lower_left.x*axis.x + rect.lower_left.y*axis.y)/((axis.x)^2 + (axis.y)^2))*axis.y;
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
