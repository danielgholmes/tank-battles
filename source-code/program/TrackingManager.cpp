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
    for(; _trackables_itterator != _trackables.end();)
    {
        //Convert Itterator to Weak Pointer
        std::weak_ptr<Trackable> entity_track_wp = (*_trackables_itterator);
        //Convert Weak Pointer to Shared Pointer
        std::shared_ptr<Trackable> entity_track_sp = entity_track_wp.lock();
        //Check to see if entity still exists
        if (entity_track_sp)
        {
            if(entity_track_sp->getType() == p1_tank)
            {
                _p1PositionX = entity_track_sp->getPositionX();
                _p1PositionY = entity_track_sp->getPositionY();
                _p1Rotation = entity_track_sp->getOrientation();
            }

            if(entity_track_sp->getType() == p2_tank)
            {
                _p2PositionX = entity_track_sp->getPositionX();
                _p2PositionY = entity_track_sp->getPositionY();
                _p2Rotation = entity_track_sp->getOrientation();
            }

            _trackables_itterator++;
        }//If (shared pointer)
        else
        {
            _trackables.erase(_trackables_itterator);
        }
    }//For

}

///Return x position of P1 Tank
const float TrackingManager::getP1PositionX()
{
    return _p1PositionX;
}

///Return y position of P1 Tank
const float TrackingManager::getP1PositionY()
{
    return _p1PositionY;
}


///Return rotation of P1 Tank
const float TrackingManager::getP1Rotation()
{
    return _p1Rotation;
}

///Return x position of P2 Tank
const float TrackingManager::getP2PositionX()
{
    return _p2PositionX;
}

///Return y position of P2 Tank
const float TrackingManager::getP2PositionY()
{
    return _p2PositionY;
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
