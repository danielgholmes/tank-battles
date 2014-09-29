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
void DestructionManager::manage(game_state_info& game_state)
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
                    game_state.player2_score++;
                    game_state.player1_respawn = true;
                }

                if (entity_sp->getType() == p2_tank)
                {
                    game_state.player1_score++;
                    game_state.player2_respawn = true;
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

void DestructionManager::addNewEntity(std::shared_ptr<Deletable> new_entity)
{
	_destructables.push_back(new_entity);
}
