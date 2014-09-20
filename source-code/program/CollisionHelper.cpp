/**
 * \file 	CollisionHelper.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	19 September 2014
 * \brief 	Implementation
 */

#include "CollisionHelper.h"
#include <vector>

bool CollisionHelper::isCollision(const rect_corners& rect_A,const rect_corners& rect_B)
{
	coordinate axis;

	axis.x = rect_A.upper_right.x - rect_A.upper_left.x;
    axis.y = rect_A.upper_right.y - rect_A.upper_left.y;
    if (!isRectangleOverlapForAxis(axis, rect_A, rect_B))
    	return false;

    axis.x = rect_A.upper_right.x - rect_A.lower_right.x;
    axis.y = rect_A.upper_right.y - rect_A.lower_right.y;
    if (!isRectangleOverlapForAxis(axis, rect_A, rect_B))
    	return false;

    axis.x = rect_B.upper_left.x - rect_B.lower_left.x;
    axis.y = rect_B.upper_left.y - rect_B.lower_left.y;
    if (!isRectangleOverlapForAxis(axis, rect_A, rect_B))
    	return false;

    axis.x = rect_B.upper_left.x - rect_B.upper_right.x;
    axis.y = rect_B.upper_left.y - rect_B.upper_right.y;
    if (!isRectangleOverlapForAxis(axis, rect_A, rect_B))
    	return false;

    return true;
}

bool CollisionHelper::isRectangleOverlapForAxis(coordinate axis,const rect_corners& rect_A, const rect_corners& rect_B)
{
	float max_A = 0.0;
	float min_A = 0.0; // scalar values of dot products between axis and projection
	float max_B = 0.0;
	float min_B = 0.0;

    std::vector<coordinate> axis_projections_A;
    std::vector<coordinate> axis_projections_B;

    calculateVectorProjections(axis_projections_A, rect_A, axis);
    calculateVectorProjections(axis_projections_B, rect_B, axis);

    calculateMaxAndMinProjectionMagnitude(axis_projections_A, rect_A, axis, max_A, min_A);
    calculateMaxAndMinProjectionMagnitude(axis_projections_B, rect_B, axis, max_B, min_B);

    if ((min_B <= max_A) && (max_B >= min_A))
    	return true;
    else
    	return false;
}

void CollisionHelper::calculateVectorProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis)
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


void CollisionHelper::calculateMaxAndMinProjectionMagnitude(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min)
{
	std::vector<float> projection_pos; // container that will indicate the projection position along axis

	auto projection = axis_projections.begin();
	for (; projection != axis_projections.end(); ++projection)
		projection_pos.push_back(((projection->x)*axis.x) + ((projection->y)*axis.y));

	min = *std::min_element(projection_pos.begin(), projection_pos.end());
	max = *std::max_element(projection_pos.begin(), projection_pos.end());
}





