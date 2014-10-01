/**
 * \file 	GeometryEngine.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	27 September 2014
 * \brief 	Implementation
 */

#include "GeometryEngine.h"
#include <vector>
#include <cmath>

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

bool GeometryEngine::isInLineOfFire(const float& rotation, const rect_corners& shooter, const rect_corners& target, const float& shooter_y, const float& target_y)
{
    coordinate axis;

    //develop axis based on the rotation of the shooter
    axis.x = shooter.lower_left.x - shooter.upper_left.x; //axis along the turret barrel
    axis.y = shooter.lower_left.y - shooter.upper_left.y;

    if (rotation >= 180.0 && rotation <= 359.0)
    {
        if (isRectangleOverlapForAxis(axis, shooter, target))
        { // also check if the target is above the shooter
            if ((target_y <= shooter_y) && (target.upper_right.y <= shooter_y) && (target.upper_left.y <= shooter_y)
                                        && (target.lower_right.y <= shooter_y) && (target.lower_left.y <= shooter_y))
                return true;
        }
    }
    else if (rotation >= 0.0 && rotation <= 179.0)
    {
        if (isRectangleOverlapForAxis(axis, shooter, target))
        { // also check if the target is below the shooter
            if ((target_y >= shooter_y) && (target.lower_right.y >= shooter_y) && (target.lower_left.y >= shooter_y)
                                        && (target.upper_right.y >= shooter_y) && (target.upper_left.y >= shooter_y))
                return true;
        }
    }

    return false;
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


const float GeometryEngine::calculateVectorLength(const float x_coord_1, const float y_coord_1, const float x_coord_2, const float y_coord_2)
{
    return (sqrt(pow((x_coord_1 - x_coord_2),2) + pow((y_coord_1 - y_coord_2),2)));
}

const blocked_status GeometryEngine::getRelativePosition(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if(lowwerPointsAboveTopOfObject(rect_entity,compared_rect_entity))
    {
        return blocked_vertically;
    }

    if(upperPointsBelowBottomOfObject(rect_entity,compared_rect_entity))
    {
        return blocked_vertically;
    }

    if(rightPointsLeftOfObject(rect_entity,compared_rect_entity))
    {
        return blocked_horizontally;
    }

    if(leftPointsRightOfObject(rect_entity,compared_rect_entity))
    {
        return blocked_horizontally;
    }
}

bool GeometryEngine::lowwerPointsAboveTopOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.lower_left.y <= compared_rect_entity.upper_left.y) &&
        (rect_entity.lower_right.y <= compared_rect_entity.upper_right.y))
            return true;
    else return false;
}

bool GeometryEngine::upperPointsBelowBottomOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if((rect_entity.upper_left.y >= compared_rect_entity.lower_left.y) &&
       (rect_entity.upper_right.y >= compared_rect_entity.lower_right.y))
            return true;
    else return false;
}

bool GeometryEngine::rightPointsLeftOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.lower_right.x <= compared_rect_entity.lower_left.x) &&
        (rect_entity.upper_right.x <= compared_rect_entity.upper_left.x))
            return true;
    else return false;
}

bool GeometryEngine::leftPointsRightOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.upper_left.x >= compared_rect_entity.lower_right.x) &&
        (rect_entity.lower_left.x >= compared_rect_entity.lower_right.x))
            return true;
    else return false;
}

