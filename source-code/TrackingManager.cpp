//! Manager responsible for keeping track of game entity positions
/*! This manager uses a lot of getter funtions in order to determine positions of the
    game entities. These values are stored as temporary private data variables.
    \file       TrackingManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#include "TrackingManager.h"

//! Constructor that initialises the _geometry_engine
/*!
*/
TrackingManager::TrackingManager():
    _geometry_engine()
{

}

TrackingManager::~TrackingManager()
{

}

//! Manage function allowing the position of all Trackable entities to be kept
/*! This includes the tracking of the tanks by the turrets. The positions are obtained and then
    passed to the _geometry_engine where comparisons are made.
    \param action_data_container :: Will set turret file in this container if needs be
*/
void TrackingManager::manage(ActionData& action_data_container)
{
    removeGarbage();
    //Clear position vectors for new cycle
    _turretPositionsX.clear();
    _turretPositionsY.clear();
    _turretRotations.clear();

    auto _trackables_itterator = _trackables.begin();
    for(; _trackables_itterator != _trackables.end(); _trackables_itterator++)
    {
        //Convert Itterator to Weak Pointer
        std::weak_ptr<Trackable> entity_track_wp = (*_trackables_itterator);
        //Convert Weak Pointer to Shared Pointer
        std::shared_ptr<Trackable> entity_track_sp = entity_track_wp.lock();
        //Check to see if entity still exists

            if(entity_track_sp->getType() == p1_tank)
            {
                _p1PositionX = entity_track_sp->getPositionX();
                _p1PositionY = entity_track_sp->getPositionY();
                _p1Rotation = entity_track_sp->getOrientation();
                _p1BoundingBox = entity_track_sp->getTrackingBoundingBox();
            }

            else if(entity_track_sp->getType() == p2_tank)
            {
                _p2PositionX = entity_track_sp->getPositionX();
                _p2PositionY = entity_track_sp->getPositionY();
                _p2Rotation = entity_track_sp->getOrientation();
                _p2BoundingBox = entity_track_sp->getTrackingBoundingBox();
            }

            else if(entity_track_sp->getType() == turret)
            {
                //Temp variables
                float temp_Turret_Xpos = entity_track_sp->getPositionX();
                float temp_Turret_Ypos = entity_track_sp->getPositionY();
                float temp_Turret_Rotation = entity_track_sp->getOrientation();
                auto temp_Turret_BoundingBox = entity_track_sp->getTrackingBoundingBox();

                //See if turrets are viewing (tank1 or tank2) and it is in proximity
                //Using case gaurds
                if((_geometry_engine.isInLineOfFire(temp_Turret_Rotation, temp_Turret_BoundingBox, _p1BoundingBox, temp_Turret_Ypos, _p1PositionY)) &&
                   (_geometry_engine.calculateVectorLength(temp_Turret_Xpos,temp_Turret_Ypos,_p1PositionX,_p2PositionY) < 400.0))
                {
                    action_data_container.setTurretFire();
                    _turretPositionsX.push_back(temp_Turret_Xpos);
                    _turretPositionsY.push_back(temp_Turret_Ypos);
                    _turretRotations.push_back(temp_Turret_Rotation);
                }

                if((_geometry_engine.isInLineOfFire(temp_Turret_Rotation, temp_Turret_BoundingBox, _p2BoundingBox, temp_Turret_Ypos, _p2PositionY)) &&
                   (_geometry_engine.calculateVectorLength(temp_Turret_Xpos,temp_Turret_Ypos,_p2PositionX,_p2PositionY) < 400.0))
                {
                    action_data_container.setTurretFire();
                    _turretPositionsX.push_back(temp_Turret_Xpos);
                    _turretPositionsY.push_back(temp_Turret_Ypos);
                    _turretRotations.push_back(temp_Turret_Rotation);
                }
            }
    }//For
}//function

//! Clear all deleted pointers.
/*!
*/
void TrackingManager::removeGarbage()
{
    //Clear all deleted entities from the _trackables vector
    auto removal = _trackables.begin();
    for (; removal != _trackables.end();)
    {
        std::weak_ptr<Trackable> removal_wp = (*removal);
		//Convert weak_ptr to shared_ptr
		std::shared_ptr<Trackable> removal_sp = removal_wp.lock();
		//Test if pointer still valid
		if(removal_sp)
        {
            removal++;
        }
        else
        {
            _trackables.erase(removal);
        }
    }// if
}//function

//! Return x position of all Turrets
/*!
*/
const std::vector<float>& TrackingManager::getTurretPositionsX()
{
    return _turretPositionsX;
}


//! Return y position of all Turrets
/*!
*/
const std::vector<float>& TrackingManager::getTurretPositionsY()
{
    return _turretPositionsY;
}

//! Return rotation of all Turrets
/*!
*/
const std::vector<float>& TrackingManager::getTurretRotations()
{
    return _turretRotations;
}

//! Return x position of P1 Tank
/*!
*/
const float TrackingManager::getP1PositionX()
{
    return _p1PositionX;
}

//! Return y position of P1 Tank
/*!
*/
const float TrackingManager::getP1PositionY()
{
    return _p1PositionY;
}


//! Return rotation of P1 Tank
/*!
*/
const float TrackingManager::getP1Rotation()
{
    return _p1Rotation;
}

//! Return x position of P2 Tank
/*!
*/
const float TrackingManager::getP2PositionX()
{
    return _p2PositionX;
}

//! Return y position of P2 Tank
/*!
*/
const float TrackingManager::getP2PositionY()
{
    return _p2PositionY;
}

//! Return rotation of P2 Tank
/*!
*/
const float TrackingManager::getP2Rotation()
{
    return _p2Rotation;
}

//! Add Trackable-type shared_ptr's to the TrackingManagers internal data members
/*!
*/
void TrackingManager::addNewEntity(std::weak_ptr<Trackable> new_entity)
{
    _trackables.push_back(new_entity);
}
