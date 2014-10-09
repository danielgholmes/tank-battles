//! Manager responsible for controlling the turrets rotation.
/*! The manager controls all the turrets movements during each program cycle
    \file       TurretManager.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/

 #ifndef TURRETMANAGER_H_
 #define TURRETMANAGER_H_

 #include "Manager.h"
 #include "Structures.h"
 #include "Turret.h"

/// Manager responsible for controlling the turrets rotation.
 class TurretManager: public Manager
 {
 public:
     TurretManager();
     void manage();
     void addNewEntity(std::weak_ptr<Turret> new_entity);
     virtual ~TurretManager();

 private:
    /// Container for all weak pointers to game turret entities
    std::vector<std::weak_ptr<Turret>> _turretables; 
    void removeGarbage();
 };

 #endif // TURRETMANAGER_H_
