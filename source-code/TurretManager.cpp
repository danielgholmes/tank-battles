//! Manager responsible for controlling the turrets rotation.
/*! The manager controls all the turrets movements during each program cycle
    \file       TurretManager.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

#include "TurretManager.h"

TurretManager::TurretManager()
{

}

TurretManager::~TurretManager()
{

}

//! Manage turret movements
/*! All turrets are simply rotated each time the manager runs
*/
void TurretManager::manage()
{
    //Clear the vector of deleted turret entities
    removeGarbage();

    auto turret_iterator = _turretables.begin();
    for (; turret_iterator !=  _turretables.end(); turret_iterator ++)
    {
        //Convert iterator to Weak pointer
        std::weak_ptr<Turret> entity_tur_wp = (*turret_iterator);

        //Lock as Shared Pointer
        std::shared_ptr<Turret> entity_tur_sp = entity_tur_wp.lock();

        entity_tur_sp->rotateTurret();
    }
}

//! Add a new weak pointer to a game turrt
/*! All the turrets have weak pointers stored in the TurretManager private vector.
*/
void TurretManager::addNewEntity(std::weak_ptr<Turret> new_entity)
{
    _turretables.push_back(new_entity);
}

//! Removed weak pointers of objects that have been deleted
/*!
*/
void TurretManager::removeGarbage()
{
    auto removable = _turretables.begin();
    for (; removable != _turretables.end();)
    {
        //Convert iterator to Weak pointer
        std::weak_ptr<Turret> removable_wp = (*removable);
        //Lock as Shared Pointer
        std::shared_ptr<Turret> removable_sp = removable_wp.lock();
        //Test to see if the shared pointer exists
        if (removable_sp)
        {
            removable++;
        }
        else
        {
            _turretables.erase(removable);
        }
    }
}
