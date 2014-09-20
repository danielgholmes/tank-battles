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
    /// Pointers to all collidable entities within the game world
    std::vector<std::weak_ptr<Collidable>> _collidables;

    /// Function that determines if there is a collision between two rectangles
    bool isCollision(const rect_corners& rect_A, const rect_corners& rect_B);

    /// Function that checks the actual overlap of the rectangles using the separating axis theorem
    bool isOverlap(const coordinate& axis, const rect_corners& rect_A, const rect_corners& rect_B);

    /// Calculates all the projections of the vertices of a rectangle onto an axis
    void calculateAllProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis);

    /// Determines the maximum and minimum projections of the rectangle vertices
    void calculateMaxAndMinProjections(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min);

	/// Set collision state based on the types of entities that have collided
	void setCollisionStates(std::shared_ptr<Collidable> entity_1, std::shared_ptr<Collidable> entity_2);

	/// Resets the blocked states of blocks that were previously blocked, by are not colliding with anything
	void resetBlockedState(std::shared_ptr<Collidable>& entity);

};

#endif // COLLISIONMANAGER_H_
