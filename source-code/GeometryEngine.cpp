//! Class responisible for handling geometrical calculations.
/*! This class is performs functions that relate to geometry in a Cartesian plane. It depends
    heavily upon the rect_corners struct for almost all its functions.  It makes use of the
    separating axis theorem quite extensively.
    \file       GeometryEngine.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#include "GeometryEngine.h"
#include <vector>
#include <cmath>

//! Determines if two rectangles have collided
/*! Throws an exception if invald arguments are given. The function goes through each axis
    projections checking for an overlap.
    \param rect_A :: Rectangle A
    \param rect_B :: Rectangle B
    \return bool
*/
bool GeometryEngine::isCollision(const rect_corners& rect_A,const rect_corners& rect_B)
{
    if (!isValidRectEntity(rect_A)) throw InvalidRectEntityProvided();
    if (!isValidRectEntity(rect_B)) throw InvalidRectEntityProvided();

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

//! Determines rectangle is inline of sight of another.
/*! Uses the shooter rotation to determine what angle the turret is sitting at. Based on this 
    angle, the turrt will behave differently. This is because, using the separating axis theorem
    creates a single axis for two opposites sides of a square. This is why a shooter would detect something 
    from behind
    \param rotation :: shooter rotation
    \param shooter :: rectangle corners of the shooter
    \param target :: rectangle corners of the target
    \return bool
*/
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

//! Determines if there is an overlap on this axis.
/*! Overlaps are calculated for axis projected axis. The projections for both reactangles A and B are compared.
    \param axis :: and x y vector
    \param rect_A :: rectangle corners of A
    \param rect_B :: rectangle corners of B
    \return bool
*/
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

//! Calculates axis projections from rectangle vertices onto an axis.
/*! \param axis_projections :: holds the projected axis values
    \param rect :: rectangle whose vertice projections are being calculated from
    \param axis :: used for the calculations
    \return bool
*/
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

//! Determines which projections are the greatest
/*! Values for A and B are claculated and passed back by reference
    \param axis_projections :: holds the projected axis values
    \param rect :: rectangle whose vertice projections are being calculated from
    \param axis :: used for the calculations
    \param max :: largest projection value saved here
    \param min :: smallers projection value saved here
    \return bool
*/
void GeometryEngine::calculateMaxAndMinProjectionMagnitude(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min)
{
	std::vector<float> projection_pos; // container that will indicate the projection position along axis

	auto projection = axis_projections.begin();
	for (; projection != axis_projections.end(); ++projection)
		projection_pos.push_back(((projection->x)*axis.x) + ((projection->y)*axis.y));

	min = *std::min_element(projection_pos.begin(), projection_pos.end());
	max = *std::max_element(projection_pos.begin(), projection_pos.end());
}

//! Calculates vector distance
/*! Used for determing if some geometrical object falls with a certain radius of the other
    \param x_coord_1 :: holds the projected axis values
    \param y_coord_1 :: rectangle whose vertice projections are being calculated from
    \param x_coord_2 :: used for the calculations
    \param y_coord_2 :: largest projection value saved here
    \return const float
*/
const float GeometryEngine::calculateVectorLength(const float x_coord_1, const float y_coord_1, const float x_coord_2, const float y_coord_2)
{
    return (sqrt(pow((x_coord_1 - x_coord_2),2) + pow((y_coord_1 - y_coord_2),2)));
}

//! Calculates vector distance
/*! Throws exception if rectangles are not valid data type.
    \param x_coord_1 :: holds the projected axis values
    \param y_coord_1 :: rectangle whose vertice projections are being calculated from
    \param x_coord_2 :: used for the calculations
    \param y_coord_2 :: largest projection value saved here
    \return const float
*/
const blocked_status GeometryEngine::getRelativePosition(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if (!isValidRectEntity(rect_entity)) throw InvalidRectEntityProvided();
    if (!isValidRectEntity(compared_rect_entity)) throw InvalidRectEntityProvided();

    blocked_status blocked_state = unblocked;

    if(upperPointsBelowBottomOfObject(rect_entity,compared_rect_entity))
    {
        blocked_state =  blocked_vertically;
    }

    else if(rightPointsLeftOfObject(rect_entity,compared_rect_entity))
    {
        blocked_state = blocked_horizontally;
    }

    else if(leftPointsRightOfObject(rect_entity,compared_rect_entity))
    {
        blocked_state = blocked_horizontally;
    }

    else if(lowwerPointsAboveTopOfObject(rect_entity,compared_rect_entity))
    {
        blocked_state = blocked_vertically;
    }

    return blocked_state;
}

//! Compares points of two rectangles
/*! Compared upper left and right y coordinate points.
    \param rect_entity :: holds the projected axis values
    \param compared_rect_entity :: rectangle whose vertice projections are being calculated from
    \return bool
*/
bool GeometryEngine::lowwerPointsAboveTopOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.upper_left.y >= compared_rect_entity.upper_left.y) &&
        (rect_entity.upper_right.y >= compared_rect_entity.upper_right.y))
            return true;
    else return false;
}

//! Compares points of two rectangles
/*! Compared lower left and right y coordinate points.
    \param rect_entity :: holds the projected axis values
    \param compared_rect_entity :: rectangle whose vertice projections are being calculated from
    \return bool
*/
bool GeometryEngine::upperPointsBelowBottomOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if((rect_entity.lower_left.y <= compared_rect_entity.lower_left.y) &&
       (rect_entity.lower_right.y <= compared_rect_entity.lower_right.y))
            return true;
    else return false;
}

//! Compares points of two rectangles
/*! Compared lower left and right y coordinate points. Also checks to see if one is right of the other. 
    \param rect_entity :: holds the projected axis values
    \param compared_rect_entity :: rectangle whose vertice projections are being calculated from
    \return bool
*/
bool GeometryEngine::rightPointsLeftOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.lower_left.x <= compared_rect_entity.lower_left.x) &&
        (rect_entity.upper_left.x <= compared_rect_entity.upper_left.x))
            return true;
    else return false;
}

//! Compares points of two rectangles
/*! Compared upper left and right y coordinate points. Also checks to see if one is left of the other.
    \param rect_entity :: holds the projected axis values
    \param compared_rect_entity :: rectangle whose vertice projections are being calculated from
    \return bool
*/
bool GeometryEngine::leftPointsRightOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity)
{
    if ((rect_entity.upper_right.x >= compared_rect_entity.upper_right.x) &&
        (rect_entity.lower_right.x >= compared_rect_entity.lower_right.x))
            return true;
    else return false;
}

//! Checks if the rectangle enrty is valid
/*! \param rect_entity :: rectangle that is being checked
    \return bool
*/
bool GeometryEngine::isValidRectEntity(const rect_corners& rect_entity)
{
    if (rect_entity.lower_left.x < -100) return false;
    else if (rect_entity.lower_right.x < -100) return false;
    else if (rect_entity.upper_left.x < -100) return false;
    else if (rect_entity.upper_right.x < -100) return false;

    else if (rect_entity.lower_left.y < -100) return false;
    else if (rect_entity.lower_right.y < -100) return false;
    else if (rect_entity.upper_left.y < -100) return false;
    else if (rect_entity.upper_right.y < -100) return false;
    else return true;

}

