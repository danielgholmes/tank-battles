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
#include "SFML/Graphics.hpp"
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

	///Return position of P1 Tank
	const sf::Vector2f getP1Position();

	///Return rotation of P1 Tank
	const float getP1Rotation();

	///Return position of P2 Tank
	const sf::Vector2f getP2Position();

	///Return rotation of P2 Tank
	const float getP2Rotation();

	/// Destructor for Tracking manager
	virtual ~TrackingManager();


private:

	// Pointers to all trackable entities within the game world
    std::vector<std::weak_ptr<Trackable>> _trackables;
    //P1's tank current rotation
    float _p1Rotation;
    //P1's tank current position
    sf::Vector2f _p1Position;
    //P2's tank current rotation
    float _p2Rotation;
    //P2's tank current position
    sf::Vector2f _p2Position;


};

#endif // TRACKINGMANAGER_H_

