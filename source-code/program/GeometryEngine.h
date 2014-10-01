/**
 * \class   GeometryEngine
 * \file 	GeometryEngine.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	27 September 2014
 * \brief 	Class that takes care of all geometrical calculations
 */

#ifndef GEOMETRYENGINE_H_
#define GEOMETRYENGINE_H_

//See this file for defenition of rect_corners
#include "Structures.h"

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

    ///Helper functions
    bool lowwerPointsAboveTopOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);

    bool upperPointsBelowBottomOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);

    bool rightPointsLeftOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);

    bool leftPointsRightOfObject(const rect_corners& rect_entity, const rect_corners& compared_rect_entity);

};

#endif // GEOMETRYENGINE_H_
