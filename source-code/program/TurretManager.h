/**
 * \class   TurretManager
 * \file 	TurretManager.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	2 September 2014
 * \brief 	Class that manages all Turret objects
 */

 #ifndef TURRETMANAGER_H_
 #define TURRETMANAGER_H_

 #include "Manager.h"
 #include "Structures.h"
 #include "Turret.h"

 class TurretManager: public Manager
 {
 public:

     ///Constructor
     TurretManager();

     ///Function called to manager the movement state of all objects
     void manage();

     ///Function to add new Turret entities to the manager
     void addNewEntity(std::weak_ptr<Turret> new_entity);

     ///Destructor
     virtual ~TurretManager();

 private:

    std::vector<std::weak_ptr<Turret>> _turretables; // =P
    void removeGarbage();

 };

 #endif // TURRETMANAGER_H_
