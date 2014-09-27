/**
 * \class 	TrackingManager
 * \file 	TrackingManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that manages all world managers
 */

#ifndef TRACKINGMANAGER_H_
#define TRACKINGMANAGER_H_

//Forward Declarations

//Includes
#include "Manager.h"
#include "Trackable.h"
#include "GeometryEngine.h"

class TrackingManager: public Manager
{
public:

	///Constructor for Tracking manager
	TrackingManager();

	///Manage function allowing the position of all Trackable entities to be kept
    void manage(actions_info& actions);

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

	// Pointers to all trackable entities within the game world
    std::vector<std::weak_ptr<Trackable>> _trackables;

    //Remove all deleted entities from _trackables
    void removeGarbage();

    //Helper Engine
    GeometryEngine _geometry_engine;

    //P1's tank current rotation
    float _p1Rotation;
    //P1's tank current x position
    float _p1PositionX;
    //P1's tank current y position
    float _p1PositionY;
    //P1's Bounding box
    rect_corners _p1BoundingBox;

    //P2's tank current rotation
    float _p2Rotation;
    //P2's tank current x position
    float _p2PositionX;
    //P2's tank current y position
    float _p2PositionY;
    //P2's Bounding box
    rect_corners _p2BoundingBox;

    //All of the Turrets current x positions
    std::vector<float> _turretPositionsX;
    //All of the Turrets current y positions
    std::vector<float> _turretPositionsY;
    //all of the Turrets current Rotations
    std::vector<float> _turretRotations;


};

#endif // TRACKINGMANAGER_H_

