/**
 * \file 	CollisionHelper.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	19 September 2014
 * \brief 	Helper class for CollisionManager that determines if there is a collision between two rectangles
 */

/*NOTE: Hightly coupled to CollisionManager. Data members are made public for testing purposes.*/

#ifndef COLLISIONHELPER_H_
#define COLLISIONHELPER_H_

//See this file for defenition of rect_corners
#include "Structures.h"

class CollisionHelper
{
public:
	///Function that client code can call to check final collision status
	bool isCollision(const rect_corners& rect_A,const rect_corners& rect_B);
	///Main function called to check overlap
	bool isRectangleOverlapForAxis(coordinate axis, const rect_corners& rect_A,const rect_corners& rect_B);
	///Calculates the projections of the rectangles vertices vectors onto an axis
	void calculateVectorProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis);
	///Calculates which of the projected vectors are furtherest along
	void calculateMaxAndMinProjectionMagnitude(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min);
};

#endif // COLLISIONHELPER_H_
