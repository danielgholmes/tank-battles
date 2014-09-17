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

class TrackingManager: public Manager
{
public:

	///Constructor for Tracking manager
	TrackingManager();

	///Manage function allowing the position of all Trackable entities to be kept
    void manage();

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

	/// Destructor for Tracking manager
	virtual ~TrackingManager();


private:

	// Pointers to all trackable entities within the game world
    std::vector<std::weak_ptr<Trackable>> _trackables;

    //P1's tank current rotation
    float _p1Rotation;
    //P1's tank current x position
    float _p1PositionX;
    //P1's tank current y position
    float _p1PositionY;

    //P2's tank current rotation
    float _p2Rotation;
    //P2's tank current x position
    float _p2PositionX;
    //P2's tank current y position
    float _p2PositionY;


};

#endif // TRACKINGMANAGER_H_

