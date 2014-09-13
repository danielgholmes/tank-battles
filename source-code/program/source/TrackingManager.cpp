/**
 * \file 	TrackingManager.cpp
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	6 September 2014
 * \brief 	implementation for the TrackingManager class
 */

#include "TrackingManager.h"

/// Constructor for Tracking manager
TrackingManager::TrackingManager()
{

}

/// Destructor for Tracking manager
TrackingManager::~TrackingManager()
{

}

/// Manage function allowing the position of all Trackable entities to be kept
void TrackingManager::manage()
{

    auto _trackables_itterator = _trackables.begin();
    for(; _trackables_itterator != _trackables.end(); _trackables_itterator++)
    {
        std::weak_ptr<Trackable> entity_wp = (*_trackables_itterator);
        if(entity_wp->getType == p1_tank)
        {
            _p1Position = entity_wp->getPosition;
            _p1Rotation = entity_wp->getOrientation;
        }

        if(entity_wp->getType == p2_tank)
        {
            _p2Position = entity_wp->getPosition;
            _p2Rotation = entity_wp->getOrientation;
        }

    }

}

///Return position of P1 Tank
const sf::Vector2f TrackingManager::getP1Position()
{
    return _p1Position;
}


///Return rotation of P1 Tank
const float TrackingManager::getP1Rotation()
{
    return _p1Rotation;
}

///Return position of P2 Tank
const sf::Vector2f TrackingManager::getP2Position()
{
    return _p2Position;
}

///Return rotation of P2 Tank
const float TrackingManager::getP2Rotation()
{
    return _p2Rotation;
}

/// Add Trackable-type shared_ptr's to the TrackingManagers internal data members
void TrackingManager::addNewEntity(std::weak_ptr<Trackable> new_entity)
{
	_trackables.push_back(new_entity);
}
