/**
 * \file 	GeometryEngine.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	27 September 2014
 * \brief 	Implementation
 */

#include "GeometryEngine.h"
#include <vector>

bool GeometryEngine::isCollision(const rect_corners& rect_A,const rect_corners& rect_B)
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

bool GeometryEngine::isInLineOfFire(const float& rotation, const rect_corners& shooter, const rect_corners& target)
{
    coordinate axis;

    //develop axis based on the rotation of the shooter
    if ((rotation >= 0.0 && rotation <= 44.0) || (rotation >= 315.0 && rotation <= 359.0))
    {
        axis.x = shooter.upper_right.x - shooter.lower_right.x;
        axis.y = shooter.upper_right.y - shooter.lower_right.y;
    }
    else if (rotation >= 45.0 && rotation <= 134.0)
    {
        axis.x = shooter.upper_left.x - shooter.upper_right.x;
        axis.y = shooter.upper_left.y - shooter.upper_right.y;
    }
    else if (rotation >= 135.0 && rotation <= 224.0)
    {
        axis.x = shooter.lower_left.x - shooter.upper_left.x;
        axis.y = shooter.lower_left.y - shooter.upper_left.y;
    }
    else if (rotation >= 225.0 && rotation >= 314.0)
    {
        axis.x = shooter.lower_left.x - shooter.lower_right.x;
        axis.y = shooter.lower_left.y - shooter.lower_right.y;
    }

    if (!isRectangleOverlapForAxis(axis, shooter, target))
    	return false;
    else
        return true;
}

bool GeometryEngine::isRectangleOverlapForAxis(coordinate axis,const rect_corners& rect_A, const rect_corners& rect_B)
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

void GeometryEngine::calculateVectorProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis)
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


void GeometryEngine::calculateMaxAndMinProjectionMagnitude(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min)
{
	std::vector<float> projection_pos; // container that will indicate the projection position along axis

	auto projection = axis_projections.begin();
	for (; projection != axis_projections.end(); ++projection)
		projection_pos.push_back(((projection->x)*axis.x) + ((projection->y)*axis.y));

	min = *std::min_element(projection_pos.begin(), projection_pos.end());
	max = *std::max_element(projection_pos.begin(), projection_pos.end());
}




