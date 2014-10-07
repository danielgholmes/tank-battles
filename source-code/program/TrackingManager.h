//! Manager responsible for keeping track of game entity positions.
/*! This manager uses a lot of getter funtions in order to determine positions of the
    game entities. These values are stored as temporary private data variables.
    \file       TrackingManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#ifndef TRACKINGMANAGER_H_
#define TRACKINGMANAGER_H_

//Forward Declarations

//Includes
#include "Manager.h"
#include "Trackable.h"
#include "GeometryEngine.h"
#include "ActionData.h"

/// Manager responsible for keeping track of game entity positions.
class TrackingManager: public Manager
{
public:

	///Constructor for Tracking manager
	TrackingManager();
	///Manage function allowing the position of all Trackable entities to be kept
    void manage(ActionData& action_data_container);
	///Add Trackable-type shared_ptr's to the TrackingManagers internal data members
    void addNewEntity(std::weak_ptr<Trackable> new_entity);
	///Return x position of P1 Tank
	const float getP1PositionX();
    ///Return y position of P1 Tank
	const float getP1PositionY();
	///Return rotation of P1 Tank
	const float getP1Rotation();
    ///Return x position of P2 Tank
	const float getP2PositionX();
    ///Return y position of P2 Tank
	const float getP2PositionY();
	///Return rotation of P2 Tank
	const float getP2Rotation();
	///Return x position of all Turrets
	const std::vector<float>& getTurretPositionsX();
	///Return y position of all Turrets
	const std::vector<float>& getTurretPositionsY();
    ///Return rotation of all Turrets
    const std::vector<float>& getTurretRotations();
	/// Destructor for Tracking manager
	virtual ~TrackingManager();


private:

	/// Pointers to all trackable entities within the game world
    std::vector<std::weak_ptr<Trackable>> _trackables;

    ///Remove all deleted entities from _trackables
    void removeGarbage();

    ///Helper Engine
    GeometryEngine _geometry_engine;

    ///Player 1 tank current rotation
    float _p1Rotation;
    ///Player 1 tank current x position
    float _p1PositionX;
    ///Player 1 tank current y position
    float _p1PositionY;
    ///Player 1 Bounding box
    rect_corners _p1BoundingBox;

    ///Player 2 tank current rotation
    float _p2Rotation;
    ///Player 2tank current x position
    float _p2PositionX;
    ///Player 2 tank current y position
    float _p2PositionY;
    ///Player 2 Bounding box
    rect_corners _p2BoundingBox;

    ///All of the Turrets current x positions
    std::vector<float> _turretPositionsX;
    ///All of the Turrets current y positions
    std::vector<float> _turretPositionsY;
    ///all of the Turrets current Rotations
    std::vector<float> _turretRotations;


};

#endif // TRACKINGMANAGER_H_

