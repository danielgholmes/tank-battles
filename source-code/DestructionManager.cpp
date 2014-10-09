//! Implementation for the DestructionManager class.
/*! The manager is responsible for removing game entities from the game that have been
    destroyed. All game entities are potentially deletable and pointers to these exist within 
    this class.
    \file       DestructionManager.cpp
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
*/
 #include "DestructionManager.h"

 ///Constructor for the Destruction manager
 DestructionManager::DestructionManager()
 {

 }
 
//! Destruction management process for the Destruction Manager
/*! If one of the tanks are destroyed, then opposing player receives an additional point.
    \param game_state_container :: cotainer that holds the players' score
*/
void DestructionManager::manage(GameStateData& game_state_container)
{
    auto i = _destructables.begin();
    for(; i != _destructables.end();)
    {
            std::shared_ptr<Deletable> entity_sp = (*i);

            //The manager checks each entity to see if it has recieved a 'death state'
            if(entity_sp->isDeleted())
            {
                if (entity_sp->getType() == p1_tank)
                {
                    game_state_container.increaseP1Score();
                }

                if (entity_sp->getType() == p2_tank)
                {
                    game_state_container.increaseP2Score();
                }

                _destructables.erase(i);
            }
            else
            {
                i++;
            }
    }
}

///Destructor for the destruction manager
DestructionManager::~DestructionManager()
{
    //Possible arguments to be added here
}

//! Add Deletable-type shared_ptr's to the DestructionManagers internal data members
/*! \param new_entity :: type of new entity that will be addded.
*/
void DestructionManager::addNewEntity(std::shared_ptr<Deletable> new_entity)
{
	_destructables.push_back(new_entity);
}
