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
    for(; i != _destructables.end(); i++)
    {
        std::weak_ptr<Deletable> entity_wp = (*i);
        //convert weak_ptr to shared ptr
        std::shared_ptr<Deletable> entity_sp = entity_wp.lock();

        //The manager checks each entity to see if it has recieved a 'death state'
        if(entity_sp->isDeleted())
        {
            delete (&entity_wp); //---> This flags a warning
        }
    }
}

///Destructor for the destruction manager
DestructionManager::~DestructionManager()
{
    //Possible arguments to be added here
}

void DestructionManager::addNewEntity(std::weak_ptr<Deletable> new_entity)
{
	_destructables.push_back(new_entity);
}
