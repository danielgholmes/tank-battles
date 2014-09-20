/**
 * /file 	DestructionManager.cpp
 * /author 	Daniel Holmes & Jonathan Gerrand
 * /date 	2 September 2014
 * /brief 	Implementation for DestructionManager class
 */

 #include "DestructionManager.h"

 ///Constructor for the Destruction manager
 DestructionManager::DestructionManager()
 {

 }

///Destruction management process for the Destruction Manager
void DestructionManager::manage()
{
    auto i = _destructables.begin();
    for(; i != _destructables.end();)
    {
            std::shared_ptr<Deletable> entity_sp = (*i);

            //The manager checks each entity to see if it has recieved a 'death state'
            if(entity_sp->isDeleted())
            {
                _destructables.erase(i);
                //delete (&entity_sp); //---> This flags a warning
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

void DestructionManager::addNewEntity(std::shared_ptr<Deletable> new_entity)
{
	_destructables.push_back(new_entity);
}
