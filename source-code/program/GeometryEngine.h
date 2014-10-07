//! Class responisible for handling geometrical calculations.
/*! This class is performs functions that relate to geometry in a Cartesian plane. It depends
	heavily upon the rect_corners struct for almost all its functions. It makes use of the
	separating axis theorem quite extensively.
    \file       GeometryEngine.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/


#ifndef GEOMETRYENGINE_H_
#define GEOMETRYENGINE_H_

//See this file for defenition of rect_corners
#include "Structures.h"

class InvalidRectEntityProvided{};

/// Class responisible for handling geometrical calculations.
class GeometryEngine
{
public:
	///Function that client code can call to check final collision status
	bool isCollision(const rect_corners& rect_A,const rect_corners& rect_B);
	///Function that checks of tank is in turrets line of fire
	bool isInLineOfFire(const float& rotation,const rect_corners& shooter,const rect_corners& target, const float& shooter_y, const float& target_y);
	///Function to determine the vector lenght between two points.
	const float calculateVectorLength(const float x_coord_1, const float y_coord_1, const float x_coord_2, const float y_coord_2);
	///Main function called to check overlap
	bool isRectangleOverlapForAxis(coordinate axis, const rect_corners& rect_A,const rect_corners& rect_B);
	///Calculates the projections of the rectangles vertices vectors onto an axis
	void calculateVectorProjections(std::vector<coordinate>& axis_projections, const rect_corners& rect, const coordinate& axis);
	///Calculates which of the projected vectors are furtherest along
	void calculateMaxAndMinProjectionMagnitude(const std::vector<coordinate>& axis_projections,const rect_corners& rect,const coordinate& axis, float& max, float& min);
	///Determine the relative positioning of two objects within the game
    const blocked_status getRelativePosition(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);

private:
    //Helper functions
    bool lowwerPointsAboveTopOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);
    bool upperPointsBelowBottomOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);
    bool rightPointsLeftOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);
    bool leftPointsRightOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);
    bool isValidRectEntity(const rect_corners& rect_entity);
};

#endif // GEOMETRYENGINE_H_
